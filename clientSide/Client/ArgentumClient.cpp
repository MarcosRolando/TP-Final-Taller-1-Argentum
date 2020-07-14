#include <netdb.h>
#include "ArgentumClient.h"
#include "ClientProtocol.h"
#include <vector>
#include <utility>
#include "BlockingQueue.hpp"
#include <SDL_mixer.h>
#include "../UpdateEvents/UpdateEvent.h"
#include "UpdateReceiver.h"
#include "GameInitializer.h"
#include "../Screen/MainMenu.h"
#include "../../libs/Timer.h"
#include "UpdateManager.h"

#define FREQUENCY 44100
#define CHUNKSIZE 2048

void Client::_processConnection() {
    //Start Menu loop
    bool quit = false;
    //GameStartInfo gameStartInfo{};
    GameGUI game;
    Timer timer;
    class MainMenu mainMenu(game.getTextureRepo().getTexture(MainMenu),
                            game.getWindow());

    mainMenu.connectLoop(quit, host, port, socket);
    Window& window = game.getWindow();
    ClientProtocol protocol(socket);
    GameInitializer initializer(game, socket, protocol);

    //mainMenu.playerSelectionLoop(quit, initializer, socket);
    //playerSelection
    initializer.loadPlayer("Ivan");
    /*if (gameStartInfo.createPlayer) {
        initializer.loadPlayer(gameStartInfo.myNickname, gameStartInfo.myRace,
                               gameStartInfo.myClass);
    } else {
        initializer.loadPlayer(gameStartInfo.myNickname);
    }*/
    char serverAcceptedConnection;
    socket.receive(&serverAcceptedConnection, sizeof(serverAcceptedConnection));

    //Game start
    initializer.initializeGame();
    BlockingQueue<std::unique_ptr<SDL_Event>> sdlEvents;
    UpdateManager updateManager;
    ClientEventHandler eventHandler(socket, quit, game, sdlEvents);
    UpdateReceiver updater(protocol, updateManager, socket, quit);
    eventHandler();
    updater();
    //Aca falta lo del main menu y la seleccion de server/player etc
    std::unique_ptr<SDL_Event> event(new SDL_Event());

    timer.start();
    game.getSoundPlayer().playMusic();
    try {
        while (!quit) {
            int updatesAvailable = updateManager.updatesAvailable();
            if (updatesAvailable > 0 && updatesAvailable < 5) {
                updatesAvailable = 1;
            }
            for (int i = 0; i < updatesAvailable; ++i) {
                auto update = updateManager.pop();
                while (!update.empty()) {
                    auto updateEvent = update.pop();
                    (*updateEvent)(game);
                }
            }
            while(SDL_PollEvent(event.get()) != 0) {
                if (!window.handleEvent(*event)) {
                    sdlEvents.push(std::move(event));
                    event.reset(new SDL_Event());
                }
            }
            double timeStep = timer.getTime();
            timer.start();
            game.getSoundPlayer().playSounds();
            game.update(timeStep);
            game.render();
            /* //todo ver si vuelvo esto porque ya tengo el vsync
            if (timeStep.count() < (1/60.f*1000)) {
                usleep((1/60.f*1000 - timeStep.count())*1000);
            }
             */
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << " in Main Game Loop" << std::endl;
    } catch (...) {
        std::cerr << "Unknown Error in Main Game Loop" << std::endl;
    }

    quit = true;
    socket.close();
    sdlEvents.doneAdding();
    eventHandler.join();
    updater.join();
}

void Client::_mainMenuLoop(GameGUI& game, bool& quit, GameStartInfo& startInfo) {
    /*class MainMenu mainMenu(game.getTextureRepo().getTexture(MainMenu),
            game.getWindow());

    //mainMenu.loop(quit, host, port, startInfo);
    mainMenu.connectLoop(quit, host, port, socket);*/
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
    //socket.connect(host, port);
    _processConnection();
}

Client::Client() : finished(false) {
    _initializeSDL();
    _setCursor();
}

void Client::_setCursor() {
    //Setea un cursor custom
    SDL_Surface *surface = nullptr;
    SDL_Cursor *cursor = nullptr;
    surface = SDL_LoadBMP("../../clientSide/Images/UI/Cursor.bmp");
    if (!surface) {
        throw TPException("No se pudo crear el cursor");
    }
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_FreeSurface(surface);
    if (!cursor) {
        throw TPException("No se pudo crear el cursor");
    }
    SDL_SetCursor(cursor);
}

void Client::_initializeSDL() {
    //Initialize Graphics
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw TPException("Graphics could not initialize! Graphics Error: %s\n", SDL_GetError());
    } else {
        //Set texture filtering to linear
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest")) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
            SDL_Quit();
            throw TPException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
    }
    if(Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2,
                                                            CHUNKSIZE) < 0) {
        IMG_Quit();
        SDL_Quit();
        throw TPException("SDL_mixer could not initialize!"
                          " SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Initialize SDL_ttf
    if(TTF_Init() == -1) {
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
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
