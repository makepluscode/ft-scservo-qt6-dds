/*
 * ServoGUI - FT SCServo Qt6 QML GUI
 * Test Mode Logic Added
 */

#include "DdsManager.hpp"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>


int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  app.setApplicationName("FT SCServo Qt6");
  app.setOrganizationName("makepluscode");

  // Check Test Mode
  bool isTestMode = false;
  for (const QString &arg : app.arguments()) {
    if (arg == "--test") {
      isTestMode = true;
      break;
    }
  }

  DdsManager ddsManager;
  if (isTestMode) {
    qInfo() << "Running in TEST MODE: Waiting for Daemon...";
    ddsManager.setTestMode(true);
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("ddsManager", &ddsManager);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  const QUrl url("qrc:/scservo/Main.qml");
  qDebug() << "Loading QML from:" << url;
  engine.load(url);

  return app.exec();
}
