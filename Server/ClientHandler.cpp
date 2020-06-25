#include "ClientHandler.h"
#include "../TPException.h"

void ClientHandler::run() {
    while (!finished) {
        try {
            std::vector<char> message;
            unsigned int bufferLength;
            _receive(message, bufferLength);
            _send(message, bufferLength);
        } catch(TPException& e) {
            finished = true; /*Hubo algun error con el cliente*/
                            /*corto la conexion*/
        }
        //if (!finished) finished = protocol.hasFinished();
    }
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


