#include "DdsManager.hpp"
#include <QDateTime>
#include <chrono>
#include <thread>

DdsManager::DdsManager(QObject *parent)
    : QObject(parent), status_("Initializing DDS...") {
  try {
    participant_ = std::make_unique<dds::domain::DomainParticipant>(0);

    dds::topic::Topic<scservo::ServoCommand> command_topic(*participant_,
                                                           "ServoCommand");
    dds::topic::Topic<scservo::ServoFeedback> feedback_topic(*participant_,
                                                             "ServoFeedback");

    dds::pub::Publisher publisher(*participant_);
    command_writer_ =
        std::make_unique<dds::pub::DataWriter<scservo::ServoCommand>>(
            publisher, command_topic);

    dds::sub::Subscriber subscriber(*participant_);
    feedback_reader_ =
        std::make_unique<dds::sub::DataReader<scservo::ServoFeedback>>(
            subscriber, feedback_topic);

    setStatus("DDS Ready - Waiting for Daemon");
    addMessage("[GUI] DDS initialized successfully");

    poll_timer_ = new QTimer(this);
    connect(poll_timer_, &QTimer::timeout, this, &DdsManager::pollFeedback);
    poll_timer_->start(50);

  } catch (const std::exception &ex) {
    setStatus(QString("DDS Error: %1").arg(ex.what()));
    addMessage(QString("[GUI] DDS initialization failed: %1").arg(ex.what()));
  }
}

DdsManager::~DdsManager() {
  if (command_writer_) {
    try {
      scservo::ServoCommand cmd;
      cmd.command_type("shutdown");
      cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count());
      command_writer_->write(cmd);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } catch (...) {
    }
  }
  if (poll_timer_)
    poll_timer_->stop();
}

void DdsManager::sendPing() {
  if (!command_writer_)
    return;

  try {
    ping_count_++;
    emit pingCountChanged();

    scservo::ServoCommand cmd;
    cmd.command_type("ping");
    cmd.servo_id(-1);
    cmd.value(ping_count_);
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());

    command_writer_->write(cmd);
    addMessage(QString("Sent PING #%1").arg(ping_count_));

  } catch (const std::exception &ex) {
    addMessage(QString("Ping failed: %1").arg(ex.what()));
  }
}

void DdsManager::sendConnect(const QString &port, int baudRate) {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("connect");
    cmd.port_name(port.toStdString());
    cmd.baud_rate(baudRate);
    command_writer_->write(cmd);
    addMessage(QString("Sending Connect to %1 @ %2").arg(port).arg(baudRate));
  } catch (const std::exception &ex) {
    addMessage(QString("Connect failed: %1").arg(ex.what()));
  }
}

void DdsManager::clearMessages() {
  messages_.clear();
  emit messagesChanged();
}

// =============================================================================
// Phase 2 Commands
// =============================================================================

void DdsManager::sendScan() {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("scan");
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());
    command_writer_->write(cmd);
    addMessage("Sent SCAN command");
  } catch (const std::exception &ex) {
    addMessage(QString("Scan failed: %1").arg(ex.what()));
  }
}

void DdsManager::sendReadState(int servoId) {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("read_state");
    cmd.servo_id(servoId);
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());
    command_writer_->write(cmd);
    addMessage(QString("Sent READ_STATE (ID: %1)").arg(servoId));
  } catch (const std::exception &ex) {
    addMessage(QString("ReadState failed: %1").arg(ex.what()));
  }
}

void DdsManager::sendWritePos(int servoId, int position, int speed, int acc) {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("write_pos");
    cmd.servo_id(servoId);
    cmd.value(position);
    cmd.speed(speed);
    cmd.acc(acc);
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());
    command_writer_->write(cmd);
    addMessage(QString("Sent WRITE_POS (ID: %1, Pos: %2, Spd: %3)")
                   .arg(servoId)
                   .arg(position)
                   .arg(speed));
  } catch (const std::exception &ex) {
    addMessage(QString("WritePos failed: %1").arg(ex.what()));
  }
}

void DdsManager::sendEnableTorque(int servoId, bool enable) {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("enable_torque");
    cmd.servo_id(servoId);
    cmd.value(enable ? 1 : 0);
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());
    command_writer_->write(cmd);
    addMessage(QString("Sent %1 TORQUE (ID: %2)")
                   .arg(enable ? "ENABLE" : "DISABLE")
                   .arg(servoId));
  } catch (const std::exception &ex) {
    addMessage(QString("EnableTorque failed: %1").arg(ex.what()));
  }
}

void DdsManager::sendDisconnect() {
  if (!command_writer_)
    return;
  try {
    scservo::ServoCommand cmd;
    cmd.command_type("disconnect");
    cmd.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                      std::chrono::system_clock::now().time_since_epoch())
                      .count());
    command_writer_->write(cmd);
    addMessage("Sent DISCONNECT command");
  } catch (const std::exception &ex) {
    addMessage(QString("Disconnect failed: %1").arg(ex.what()));
  }
}

void DdsManager::pollFeedback() {
  if (!feedback_reader_ || !command_writer_)
    return;

  try {
    auto pub_status = command_writer_->publication_matched_status();
    bool connected = pub_status.current_count() > 0;
    if (connected != daemon_connected_) {
      setDaemonConnected(connected);
      if (connected) {
        setStatus("Connected to Daemon");
        addMessage("Daemon connected!");
      } else {
        setStatus("Daemon disconnected");
        addMessage("Daemon disconnected.");
      }
    }

    auto samples = feedback_reader_->take();
    for (const auto &sample : samples) {
      if (sample.info().valid()) {
        const auto &fb = sample.data();
        std::string type = fb.feedback_type();
        std::string msg = fb.message();

        if (type == "pong") {
          pong_count_++;
          emit pongCountChanged();
          addMessage(
              QString("Received PONG: %1").arg(QString::fromStdString(msg)));

          if (test_mode_) {
            qInfo() << "TEST_SUCCESS: Pong received from Daemon";
            QCoreApplication::exit(0);
          }
        } else if (type == "ping") {
          // Daemon Heartbeat 처리
          addMessage(
              QString("[Daemon Ping] %1").arg(QString::fromStdString(msg)));
        } else if (type == "status") {
          addMessage(QString("Status: %1").arg(QString::fromStdString(msg)));
        } else if (type == "error") {
          addMessage(QString("Error: %1").arg(QString::fromStdString(msg)));
        } else if (type == "scan_result") {
          // Phase 2: Scan Result
          found_servo_ids_.clear();
          const auto &ids = fb.found_ids();
          for (const auto &id : ids) {
            found_servo_ids_.append(id);
          }
          addMessage(
              QString("Scan found %1 servos").arg(found_servo_ids_.size()));
        } else if (type == "servo_state") {
          // Phase 2: Servo State
          const auto &state = fb.state();
          addMessage(QString("Servo[%1] Pos:%2 Spd:%3 Load:%4 V:%5 T:%6")
                         .arg(state.id())
                         .arg(state.position())
                         .arg(state.speed())
                         .arg(state.load())
                         .arg(state.voltage() / 10.0)
                         .arg(state.temperature()));
        } else if (type == "ack") {
          addMessage(QString("ACK: %1").arg(QString::fromStdString(msg)));
        }
      }
    }

    // Test Logic
    if (test_mode_) {
      if (daemon_connected_ && ping_count_ == 0) {
        test_step_++;
        if (test_step_ > 10) {
          qInfo() << "TEST_INFO: Sending Ping...";
          sendPing();
        }
      } else if (!daemon_connected_) {
        static int wait_limit = 0;
        if (++wait_limit > 200) {
          qWarning() << "TEST_FAIL: Daemon discovery timeout";
          QCoreApplication::exit(1);
        }
      }
    }

  } catch (const std::exception &ex) {
    qWarning() << "Exception in pollFeedback:" << ex.what();
  } catch (...) {
    qWarning() << "Unknown exception in pollFeedback";
  }
}

void DdsManager::addMessage(const QString &msg) {
  QString timeStr = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
  messages_.prepend(QString("[%1] %2").arg(timeStr).arg(msg));
  if (messages_.size() > 100)
    messages_.removeLast();
  emit messagesChanged();
}

void DdsManager::setStatus(const QString &status) {
  if (status_ != status) {
    status_ = status;
    emit statusChanged();
  }
}

void DdsManager::setDaemonConnected(bool connected) {
  if (daemon_connected_ != connected) {
    daemon_connected_ = connected;
    emit daemonConnectedChanged();
  }
}
