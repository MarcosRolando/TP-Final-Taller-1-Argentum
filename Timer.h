//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_TIMER_H
#define ARGENTUM_TIMER_H

#include <cstdint>


class Timer {
private:
    //The clock time when the timer started
    uint32_t mStartTicks;

    //The ticks stored when the timer was paused
    uint32_t mPausedTicks;

    //The timer status
    bool mPaused;
    bool mStarted;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    uint32_t getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
};


#endif //ARGENTUM_TIMER_H
