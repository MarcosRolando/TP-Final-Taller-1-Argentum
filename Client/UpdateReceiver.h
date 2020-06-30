//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATERECEIVER_H
#define ARGENTUM_UPDATERECEIVER_H

#include "Thread.h"
#include "UpdateQueue.hpp"
#include <msgpack.hpp>

class UpdateEvent;
class Socket;

class UpdateReceiver : public Thread {
private:
    UpdateQueue<std::unique_ptr<UpdateEvent>>& updates;
    msgpack::object_handle handler;
    std::size_t offset{0};
    Socket& socket;
    std::vector<char> buffer;
    bool& quit;

public:
    UpdateReceiver(UpdateQueue<std::unique_ptr<UpdateEvent>>& _updates,
                Socket& _socket, bool& _quit) :
                    updates(_updates), socket(_socket), quit(_quit) {}

    void run() override;

private:
    void _processUpdate();
    void _processMoveUpdate();
};


#endif //ARGENTUM_UPDATERECEIVER_H
