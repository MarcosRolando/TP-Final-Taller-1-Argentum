//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEQUEUE_HPP
#define ARGENTUM_UPDATEQUEUE_HPP

#include <mutex>
#include <queue>
#include <condition_variable>
#include "../../libs/TPException.h"

template <class T>
class UpdateQueue {
private:
    std::queue<T> queue; //todo preguntarle a fefo si usar el heap o copiar 300 bytes para cada evento
    std::mutex mtx;
    bool updateAvailable{false};
    std::condition_variable cv;
public:
    void push(T element);
    T pop();
    bool empty();
    void deliverUpdate();
    bool isUpdateAvailable();
    void consumedUpdate();
};

template <typename T>
void UpdateQueue<T>::push(T element) {
    std::unique_lock<std::mutex> lock(mtx);
    while (updateAvailable) {
        cv.wait(lock);
    }
    queue.push(std::move(element));
}

template <typename T>
T UpdateQueue<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx);
    if (updateAvailable) {
        T element = std::move(queue.front());
        queue.pop();
        return element;
    }
    throw TPException("La cola bloqueante se cerro!");
}

template <typename T>
bool UpdateQueue<T>::empty() {
    return queue.empty();
}

template <typename T>
bool UpdateQueue<T>::isUpdateAvailable() {
    return updateAvailable;
}

template <typename T>
void UpdateQueue<T>::deliverUpdate() {
    std::unique_lock<std::mutex> lock(mtx);
    updateAvailable = true;
}

template <typename T>
void UpdateQueue<T>::consumedUpdate() {
    std::unique_lock<std::mutex> lock(mtx);
    updateAvailable = false;
    cv.notify_all();
}


#endif //ARGENTUM_UPDATEQUEUE_HPP
