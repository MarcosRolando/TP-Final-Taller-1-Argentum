//
// Created by marcos on 13/7/20.
//

#ifndef ARGENTUM_TIMER_H
#define ARGENTUM_TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point time1{};
    std::chrono::high_resolution_clock::time_point time2{};

public:
    //Starts the timer
    void start();

    //Returns time passed since start in milliseconds
    double getTime();
};


#endif //ARGENTUM_TIMER_H
