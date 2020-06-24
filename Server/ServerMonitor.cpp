#include "ServerMonitor.h"
#include <iostream>

const char FINISH_CHAR = 'q';

void ServerMonitor::_stopOnCommand() const {
    char input = 0;
    while (input != FINISH_CHAR) {
        std::cin >> input;
    }
    server.forceFinish();
}

void ServerMonitor::run() {
    _stopOnCommand();
}
