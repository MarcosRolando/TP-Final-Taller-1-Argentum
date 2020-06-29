//
// Created by marcos on 8/5/20.
//

#ifndef TP2TALLER_BLOCKINGQUEUE_H
#define TP2TALLER_BLOCKINGQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <SDL_events.h>

class BlockingQueue {
private:
    std::queue<std::unique_ptr<SDL_Event>> queue; //todo preguntarle a fefo si usar el heap o copiar 300 bytes para cada evento
    std::mutex mtx;
    std::condition_variable cv;
    bool finishedAdding;
public:
    BlockingQueue();
    void push(std::unique_ptr<SDL_Event> element);
    std::unique_ptr<SDL_Event> pop();
    bool empty();
    void doneAdding();
};


#endif //TP2TALLER_BLOCKINGQUEUE_H
