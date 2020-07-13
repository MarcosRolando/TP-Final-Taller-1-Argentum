//
// Created by marcos on 13/7/20.
//

#include "Timer.h"
using namespace std::chrono;

void Timer::start() {
    time1 = high_resolution_clock::now();
}

double Timer::getTime() {
    time2 = high_resolution_clock::now();
    duration<double, std::milli> timeStep = time2 - time1;
    return timeStep.count();
}
