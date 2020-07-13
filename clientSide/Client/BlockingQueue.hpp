//
// Created by marcos on 8/5/20.
//

#ifndef TP2TALLER_BLOCKINGQUEUE_H
#define TP2TALLER_BLOCKINGQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include "../../libs/TPException.h"


template <class T>
class BlockingQueue {
private:
    std::queue<T> queue; //todo preguntarle a fefo si usar el heap o copiar 300 bytes para cada evento
    std::mutex mtx;
    std::condition_variable cv;
    bool finishedAdding{false};
public:
    void push(T element);
    T pop();
    bool empty();
    void doneAdding();
};

template <typename T>
void BlockingQueue<T>::push(T element) {
    std::unique_lock<std::mutex> lock(mtx);
    queue.push(std::move(element));
    cv.notify_all();
}

template <typename T>
T BlockingQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    while (queue.empty() && !finishedAdding) {
        cv.wait(lock);
    }
    if (!queue.empty()) {
        T element = std::move(queue.front());
        queue.pop();
        return element;
    }
    throw TPException("La cola bloqueante se cerro!");
}

template <typename T>
bool BlockingQueue<T>::empty() {
    return (finishedAdding && queue.empty());
}

template <typename T>
void BlockingQueue<T>::doneAdding() {
    std::unique_lock<std::mutex> lock(mtx);
    finishedAdding = true;
    cv.notify_all();
}


#endif //TP2TALLER_BLOCKINGQUEUE_H
