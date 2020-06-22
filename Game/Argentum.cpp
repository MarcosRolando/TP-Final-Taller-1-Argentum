//
// Created by agustin on 20/6/20.
//

#include "Argentum.h"
#include <chrono>
#include <atomic>

using namespace std::chrono;

void Argentum::execute() {
    std::atomic<bool> keepRunning(true);

    high_resolution_clock::time_point time1 = high_resolution_clock::now();
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    duration<double, std::milli> timeStep = time2 - time1;
    //ACA SE TIRA THREAD PARA RECIBIR LA Q QUE CIERRA EL SERVER


    while (keepRunning) {


    }
}
