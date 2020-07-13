#include "Thread.h"

void Thread::operator()() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}
