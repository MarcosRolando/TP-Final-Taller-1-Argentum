#include "ClientHandler.h"
#include "../TPException.h"
#include "ServerProtocol.h"
#include <vector>
#include <cstdint>

#define MAX_NUMBER_OF_MESSAGES_STORED 3

void ClientHandler::run() {
    _sendMapInfoToClient();

    /*
    std::unique_lock<std::mutex> lk(m);
    //std::vector<char> buffer;

    while (!finished) {
        //socket.receive(buffer, sizeof(unit32_t));
    }
*/
}

void ClientHandler::_receive(std::vector<char>& message,
                                                unsigned int& bufferLength) {
    /*
    do {
        message = protocol.commandBuffer(bufferLength);
        socket.receive(message.data(), bufferLength);
        protocol.processCommand(message.data());
    } while (!protocol.finishedReceiving());
     */
}

void ClientHandler::_send(std::vector<char>& message,
                                                unsigned int& bufferLength) {
    //essage = protocol.getResponse(bufferLength);
    socket.send(message.data(), bufferLength);
}

bool ClientHandler::hasFinished() const {
    return finished;
}

void ClientHandler::_sendMapInfoToClient() {
    const std::vector<char>& mapInfo = protocol.getMapInfo();
    socket.send(mapInfo.data(), mapInfo.size());
}


