#include <netdb.h>
#include "ArgentumClient.h"
#include "ClientProtocol.h"
#include <cstring>
#include "User.h"
#include "../TPException.h"
#include <string>
#include <vector>
#include <utility>
#include "EventBlockingQueue.h"

void Client::_send() const {
    std::string command = User::getInput();
    //unsigned int bufferLength;
    //std::vector<char> buffer = ClientProtocol::translateCommand(std::move(command), bufferLength);
    //socket.send(buffer.data(), bufferLength);
}

void Client::_receive() {
    //unsigned int bufferLength;
    std::vector<char> response;
    /*do {
        response = protocol.responseBuffer(bufferLength);
        socket.receive(response.data(), bufferLength);
        protocol.processResponse(response);
    } while (!protocol.finishedReceiving());*/
    User::showMessage(response.data());
}

void Client::_processConnection() {
    bool quit = false;
    GameGUI game;
    EventBlockingQueue events;
    ClientProtocol protocol(game, socket);
    ClientEventHandler eventHandler(quit, game, events);
    eventHandler();
    //Aca falta lo del main menu y la seleccion de server/player etc
    std::unique_ptr<SDL_Event> event(new SDL_Event());

    while (!quit) {
        while(SDL_PollEvent(event.get()) != 0) {
            events.push(std::move(event));
            event.reset(new SDL_Event());
        }
        game.render();
    }

    eventHandler.join();
    /*
    while (!finished) {
        try {
            _send();
            _receive();
        } catch(TPException& e) {
            User::showMessage(e.what());
        }
        //finished = protocol.hasFinished();
    }
    */
}

void Client::connect() {
    socket.connect(host, port);
    _processConnection();
}
