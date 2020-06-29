//
// Created by marcos on 8/5/20.
//

#include "EventBlockingQueue.h"

EventBlockingQueue::EventBlockingQueue() {
    finishedAdding = false;
}

void EventBlockingQueue::push(std::unique_ptr<SDL_Event> element) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(std::move(element));
    cv.notify_all();
}

std::unique_ptr<SDL_Event> EventBlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    while (queue.empty() && !finishedAdding) {
        cv.wait(lock);
    }
    if (!queue.empty()) {
        std::unique_ptr<SDL_Event> element = std::move(queue.front());
        queue.pop();
        return element;
    }
    return nullptr; //la alternativa era tirar una exception que es mas sidoso todavia, esto seria un nullptr
}

bool EventBlockingQueue::empty() {
    return (finishedAdding && queue.empty());
}

void EventBlockingQueue::doneAdding() {
    std::unique_lock<std::mutex> lock(mtx);
    finishedAdding = true;
    cv.notify_all();
}

