#include <netdb.h>
#include "ArgentumClient.h"
#include "ClientProtocol.h"
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
#include "../Screen/MainMenu.h"


using namespace std::chrono;

#define FREQUENCY 44100
#define CHUNKSIZE 2048

void Client::_processConnection() {
    //Start Menu loop
    bool quit = false;
    GameStartInfo gameStartInfo{};
    GameGUI game;
    _mainMenuLoop(game, quit, gameStartInfo);
    Window& window = game.getWindow();
    ClientProtocol protocol(socket);
    GameInitializer initializer(game, socket, protocol);
    initializer.loadPlayer("Ivan");

    /*if (gameStartInfo.createPlayer) {
        initializer.loadPlayer(gameStartInfo.myNickname, gameStartInfo.myRace,
                               gameStartInfo.myClass);
    } else {
        initializer.loadPlayer(gameStartInfo.myNickname);
    }*/
    char serverAcceptedConnection;
    socket.receive(&serverAcceptedConnection, sizeof(serverAcceptedConnection));
    //End menu loop

    //Game start
    initializer.initializeGame();
    BlockingQueue<std::unique_ptr<SDL_Event>> sdlEvents;
    UpdateQueue<std::unique_ptr<UpdateEvent>> updateEvents;
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
    game.getSoundPlayer().playMusic();
    try {
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
            game.getSoundPlayer().playSounds();
            game.render(timeStep.count());
            if (timeStep.count() < (1/60.f*1000)) {
                usleep((1/60.f*1000 - timeStep.count())*1000);
            }
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << " in Main Game Loop" << std::endl;
    } catch (...) {
        std::cerr << "Unknown Error in Main Game Loop" << std::endl;
    }

    quit = true;
    socket.close();
    updateEvents.consumedUpdate();
    sdlEvents.doneAdding();
    eventHandler.join();
    updater.join();
}

void Client::_mainMenuLoop(GameGUI& game, bool& quit, GameStartInfo& startInfo) {
    class MainMenu mainMenu(game.getTextureRepo().getTexture(MainMenu),
            game.getWindow());

    //mainMenu.loop(quit, host, port, startInfo);
    mainMenu.connectLoop(quit, host, port, socket);
}

void Client::connect() {
    /*bool connected = false;
    while (!connected) {
        try {
            std::cin >> host;               NO BORRAR ESTO; LO NECESITO DE REFERENCIA
            std::cin >> port;
            socket.connect(host, port);
            connected = true;//Si no tira excepcion es q conecte
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }*/
    socket.connect(host, port);
    _processConnection();
}

Client::Client(std::string &&host, std::string &&port)  : host(host), port(port),
                                                    finished(false) {
    _initializeSDL();
    _setCursor();
}

void Client::_setCursor() {
    //Setea un cursor custom
    SDL_Surface *surface = nullptr;
    SDL_Cursor *cursor = nullptr;
    surface = SDL_LoadBMP("../Images/UI/Cursor.bmp");
    if (!surface) {
        throw TPException("No se pudo crear el cursor");
    }
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    if (!cursor) {
        throw TPException("No se pudo crear el cursor");
    }
    SDL_SetCursor(cursor);
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
    if(Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                      CHUNKSIZE) < 0){
        throw TPException("SDL_mixer could not initialize!"
                          " SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Initialize SDL_ttf
    if(TTF_Init() == -1) {
        throw TPException("SDL_ttf could not initialize! SDL_ttf Error:"
                          " %s\n", TTF_GetError());
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
