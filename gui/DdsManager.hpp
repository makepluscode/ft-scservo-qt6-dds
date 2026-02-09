#pragma once

#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <memory>

#include "scservo.hpp"
#include <dds/dds.hpp>

class DdsManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString status READ status NOTIFY statusChanged)
  Q_PROPERTY(QStringList messages READ messages NOTIFY messagesChanged)
  Q_PROPERTY(
      bool daemonConnected READ daemonConnected NOTIFY daemonConnectedChanged)
  Q_PROPERTY(int pingCount READ pingCount NOTIFY pingCountChanged)
  Q_PROPERTY(int pongCount READ pongCount NOTIFY pongCountChanged)

public:
  explicit DdsManager(QObject *parent = nullptr);
  ~DdsManager() override;

  QString status() const { return status_; }
  QStringList messages() const { return messages_; }
  bool daemonConnected() const { return daemon_connected_; }
  int pingCount() const { return ping_count_; }
  int pongCount() const { return pong_count_; }
  QList<int> foundServoIds() const { return found_servo_ids_; }

  // Phase 1 Commands
  Q_INVOKABLE void sendPing();
  Q_INVOKABLE void sendConnect(const QString &port, int baudRate);
  Q_INVOKABLE void clearMessages();

  // Phase 2 Commands
  Q_INVOKABLE void sendScan();
  Q_INVOKABLE void sendReadState(int servoId);
  Q_INVOKABLE void sendWritePos(int servoId, int position, int speed, int acc);
  Q_INVOKABLE void sendEnableTorque(int servoId, bool enable);
  Q_INVOKABLE void sendDisconnect();

  // Test Mode
  void setTestMode(bool test) { test_mode_ = test; }

signals:
  void statusChanged();
  void messagesChanged();
  void daemonConnectedChanged();
  void pingCountChanged();
  void pongCountChanged();

private slots:
  void pollFeedback();

private:
  void addMessage(const QString &msg);
  void setStatus(const QString &status);
  void setDaemonConnected(bool connected);

  std::unique_ptr<dds::domain::DomainParticipant> participant_;
  std::unique_ptr<dds::pub::DataWriter<scservo::ServoCommand>> command_writer_;
  std::unique_ptr<dds::sub::DataReader<scservo::ServoFeedback>>
      feedback_reader_;

  QString status_;
  QStringList messages_;
  bool daemon_connected_ = false;
  int ping_count_ = 0;
  int pong_count_ = 0;
  QList<int> found_servo_ids_;

  QTimer *poll_timer_;

  // Test Mode State
  bool test_mode_ = false;
  int test_step_ = 0;
};
