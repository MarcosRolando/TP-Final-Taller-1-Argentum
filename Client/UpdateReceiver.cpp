//
// Created by marcos on 6/29/20.
//

#include <netinet/in.h>
#include "UpdateReceiver.h"
#include "Socket.h"
#include <msgpack.hpp>

void UpdateReceiver::run() {
    uint32_t msgLength = 0;
    std::vector<char> buffer;
    while (!quit) {
        try {
            socket.receive((char*)(&msgLength), sizeof(uint32_t));
            msgLength = ntohl(msgLength);
            buffer.resize(msgLength);
            buffer.clear();
            socket.receive(buffer.data(), msgLength);
            _proccessUpdate(buffer);
        } catch (...) {
            //do nothing
        }
    }
}

void UpdateReceiver::_proccessUpdate(std::vector<char>& buffer) {
    msgpack::type:tuple<GameType::>
}
