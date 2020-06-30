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
    bool& quit;

public:
    UpdateReceiver(BlockingQueue<std::unique_ptr<UpdateEvent>>& _updates,
                Socket& _socket, bool& _quit) :
                    updates(_updates), socket(_socket), quit(_quit) {}

    void run() override;

private:
    void _proccessUpdate(std::vector<char>& buffer);
};


#endif //ARGENTUM_UPDATERECEIVER_H
