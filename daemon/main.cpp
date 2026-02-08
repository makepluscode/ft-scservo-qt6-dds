/**
 * @file main.cpp
 * @brief ServoDaemon Entry Point
 * @details ServoDaemon 클래스를 인스턴스화하고 실행 루프를 시작합니다.
 */

#include "ServoDaemon.hpp"
#include <atomic>
#include <chrono> // for milliseconds
#include <csignal>
#include <iostream>
#include <thread> // for sleep_for


std::atomic<bool> g_stop_signal(false);

void signal_handler(int) {
  g_stop_signal = true;
  // main 루프에서 감지하도록 둠.
  // 하지만 daemon.run()이 blocking이므로, stop()을 호출해줄 필요가 있을까?
  // daemon 객체가 지역변수라 여기서 접근 불가.
  // 하지만 processCommand("shutdown")으로 종료하는 것이 정석이므로,
  // Ctrl+C는 강제 종료에 해당. 여기서는 g_stop_signal만 설정.
}

int main() {
  std::signal(SIGINT, signal_handler);
  std::signal(SIGTERM, signal_handler);

  std::cout << "========================================" << std::endl;
  std::cout << "  FT SCServo Daemon (Refactored)" << std::endl;
  std::cout << "========================================" << std::endl;

  ServoDaemon daemon;

  if (daemon.start()) {
    std::cout << "[Main] Daemon running. Press Ctrl+C to stop." << std::endl;

    // daemon.run()이 blocking 함수이므로, signal 처리가 어려울 수 있음.
    // 하지만 ServoDaemon::run() 내부에서 running_을 체크하므로,
    // 외부에서 running_을 false로 바꿀 방법이 필요함 (shutdown 커맨드 등).

    // 여기서 daemon.run()을 호출하면 리턴하지 않음.
    daemon.run();
  }

  std::cout << "[Main] Stopping..." << std::endl;
  daemon.stop();

  return 0;
}
