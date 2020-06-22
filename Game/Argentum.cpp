//
// Created by agustin on 20/6/20.
//

#include "Argentum.h"
#include <chrono>
#include <atomic>
#include <unistd.h>

#define FRAME_TIME 33

using namespace std::chrono;

void Argentum::execute() {
    std::atomic<bool> keepRunning(true);

    //ACA SE TIRA THREAD PARA RECIBIR LA Q QUE CIERRA EL SERVER


    high_resolution_clock::time_point time1;
    high_resolution_clock::time_point time2;
    duration<double, std::milli> timeStep{};
    double lastFrameTime = 0;
    while (keepRunning) {
        time1 = high_resolution_clock::now();

        game.update(lastFrameTime);


        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        lastFrameTime = timeStep.count();
        if (lastFrameTime < FRAME_TIME) {
            usleep((FRAME_TIME - lastFrameTime) * 1000);
            lastFrameTime = FRAME_TIME;
        }
    }
}
