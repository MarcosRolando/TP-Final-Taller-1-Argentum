#include <netdb.h>
#include "ArgentumClient.h"
#include "ClientProtocol.h"
#include <cstring>
#include "User.h"
#include "../TPException.h"
#include <string>
#include <vector>
#include <utility>
#include "BlockingQueue.hpp"
#include "UpdateQueue.hpp"
#include <SDL_mixer.h>
#include "../UpdateEvents/UpdateEvent.h"
#include "UpdateReceiver.h"
#include <chrono>
#include "GameInitializer.h"

using namespace std::chrono;

#define FREQUENCY 44100
#define CHUNKSIZE 2048

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
    Window& window = game.getWindow();
    BlockingQueue<std::unique_ptr<SDL_Event>> sdlEvents;
    UpdateQueue<std::unique_ptr<UpdateEvent>> updateEvents;
    ClientProtocol protocol(socket);
    GameInitializer initializer(game, socket, protocol);
    initializer.loadPlayer("manolito", GameType::Race::DWARF, GameType::Class::WARRIOR);
    initializer.initializeGame();
    ClientEventHandler eventHandler(socket, quit, game, sdlEvents);
    UpdateReceiver updater(protocol, updateEvents, socket, quit);
    eventHandler();
    updater();
    //Aca falta lo del main menu y la seleccion de server/player etc
    std::unique_ptr<SDL_Event> event(new SDL_Event());
    std::unique_ptr<UpdateEvent> update;

    high_resolution_clock::time_point time1;
    high_resolution_clock::time_point time2;
    duration<float, std::milli> timeStep{};

    time1 = high_resolution_clock::now();

    while (!quit) {
        if (updateEvents.isUpdateAvailable()) {
            while (!updateEvents.empty()) {
                update = updateEvents.pop();
                (*update)(game);
            }
            updateEvents.consumedUpdate();
        }
        while(SDL_PollEvent(event.get()) != 0) {
            if (!window.handleEvent(*event)) {
                sdlEvents.push(std::move(event));
                event.reset(new SDL_Event());
            }
        }
        time2 = high_resolution_clock::now();
        timeStep = time2 - time1;
        time1 = high_resolution_clock::now();
        game.render(timeStep.count());
    }

    socket.close();

    eventHandler.join();
    updater.join();
}

void Client::connect() {
    socket.connect(host, port);
    _processConnection();
}

Client::Client(std::string &&host, std::string &&port)  : host(host), port(port),
                                                    finished(false) {
    _initializeSDL();
}

void Client::_initializeSDL() {
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw TPException("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    } else {
        //Set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest")) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
            throw TPException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
    }
    if( Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                      CHUNKSIZE) < 0 ){
        throw TPException("SDL_mixer could not initialize!"
                          " SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){//ver si esto va en la clase SDL gral
        throw TPException("SDL_ttf could not initialize! SDL_ttf Error:"
                          " %s\n", TTF_GetError() );
    }
}

void Client::_closeSDL() {
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Client::~Client() {
    _closeSDL();
}
