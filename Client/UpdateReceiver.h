//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATERECEIVER_H
#define ARGENTUM_UPDATERECEIVER_H

#include "Thread.h"
#include "BlockingQueue.hpp"

class UpdateEvent;
class Socket;

class UpdateReceiver : public Thread {
private:
    BlockingQueue<std::unique_ptr<UpdateEvent>>& updates;
    Socket& socket;

public:
    UpdateReceiver(BlockingQueue<std::unique_ptr<UpdateEvent>>& _updates, Socket& _socket) :
                    updates(_updates), socket(_socket) {}

    void run() override;
};


#endif //ARGENTUM_UPDATERECEIVER_H
