//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEQUEUE_HPP
#define ARGENTUM_UPDATEQUEUE_HPP

#include <queue>

template <class T>
class UpdateQueue {
private:
    std::queue<T> queue;

public:
    UpdateQueue<T>() = default;
    UpdateQueue<T>(UpdateQueue<T>&& other) noexcept;
    void push(T element);
    T pop();
    bool empty();
};

template <typename T>
void UpdateQueue<T>::push(T element) {
    queue.push(std::move(element));
}

template <typename T>
T UpdateQueue<T>::pop() {
    T element = std::move(queue.front());
    queue.pop();
    return element;
}

template <typename T>
bool UpdateQueue<T>::empty() {
    return queue.empty();
}

template <typename T>
UpdateQueue<T>::UpdateQueue(UpdateQueue<T>&& other)  noexcept {
    queue = std::move(other.queue);
}


#endif //ARGENTUM_UPDATEQUEUE_HPP
