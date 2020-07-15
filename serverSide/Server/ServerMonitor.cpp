#include "ServerMonitor.h"
#include <iostream>

const char FINISH_CHAR = 'q';

void ServerMonitor::_stopOnCommand() {
    char input = 0;
    while (input != FINISH_CHAR) {
        input = std::getchar();
    }
    reading = false;
    server.finish();
}

void ServerMonitor::run() {
    _stopOnCommand();
}

void ServerMonitor::join() {
    if (reading) {
        Thread::detach();
    } else {
        Thread::join();
    }
}
