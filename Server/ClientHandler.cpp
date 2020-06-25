#include "ClientHandler.h"
#include "../TPException.h"
#include "ServerProtocol.h"

void ClientHandler::run() {
    _sendMapInfoToClient();
    /*
    while (!finished) {
        try {
            std::vector<char> message;
            unsigned int bufferLength;
            _receive(message, bufferLength);
            _send(message, bufferLength);
        } catch(TPException& e) {
            finished = true; //Hubo algun error con el cliente corto la conexion
        //}
        //if (!finished) finished = protocol.hasFinished();
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


