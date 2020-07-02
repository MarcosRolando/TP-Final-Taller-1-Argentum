//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATERECEIVER_H
#define ARGENTUM_UPDATERECEIVER_H

#include "Thread.h"
#include "UpdateQueue.hpp"
#include "ClientProtocol.h"
#include <msgpack.hpp>

class UpdateEvent;
class Socket;

class UpdateReceiver : public Thread {
private:
    ClientProtocol& protocol;
    UpdateQueue<std::unique_ptr<UpdateEvent>>& updates;
    msgpack::object_handle handler;
    std::size_t offset{0};
    Socket& socket;
    std::vector<char> buffer;
    bool& quit;

public:
    UpdateReceiver(ClientProtocol& protocol,UpdateQueue<std::unique_ptr<UpdateEvent>>& _updates,
                Socket& _socket, bool& _quit) : protocol(protocol),
                    updates(_updates), socket(_socket), quit(_quit) {}

    void run() override;

private:
    void _processUpdate(uint32_t msgLength);
    void _processMoveUpdate();

    void _processCreateEntity();
};


#endif //ARGENTUM_UPDATERECEIVER_H