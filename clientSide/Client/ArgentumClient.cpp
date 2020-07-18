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
#include "UpdateManager.h"

#define FREQUENCY 44100
#define CHUNKSIZE 2048
#define CURSOR_PATH "../../clientSide/Assets/Images/UI/Cursor.bmp"


void Client::_gameLoop() {
    bool quit = false;
    GameGUI game;
    Timer timer;
    class MainMenu mainMenu(game.getTextureRepo().getTexture(MainMenu),
                            game.getWindow());
    Window& window = game.getWindow();
    ClientProtocol protocol(socket);
    GameInitializer initializer(game, socket, protocol);

    /* Loop del menu principal */
    mainMenu.menuScreen(quit, initializer, socket);

    if (quit) return;//Si elegi salir del juego en el menu no tengo que hacer nada mas

    initializer.initializeGame();

    BlockingQueue<std::unique_ptr<SDL_Event>> sdlEvents;
    UpdateManager updateManager;
    ClientEventHandler eventHandler(socket, quit, game, sdlEvents);
    UpdateReceiver updater(protocol, updateManager, socket, quit);
    std::unique_ptr<SDL_Event> event(new SDL_Event());

    /* Se lanzan los dos threads que van a manejar los eventos de input de usuario
     * y los recibidos por el server respectivamente */
    eventHandler();
    updater();

    timer.start();
    game.getSoundPlayer().playMusic();
    double timeStep;

    try {
        while (!quit) {
            //Eventos de input del usuario
            while(SDL_PollEvent(event.get()) != 0) {
                if (!window.handleEvent(*event)) {
                    sdlEvents.push(std::move(event));
                    event.reset(new SDL_Event());
                }
            }

            //Eventos recibidos por el servidor
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
                timeStep = timer.getTime();
                timer.start();
                game.update(timeStep);
            }

            game.getSoundPlayer().playSounds();
            game.render();
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

void Client::run() {
    _gameLoop();
}

Client::Client(){
    _initializeSDL();
    _setCursor();
}

//Setea un cursor custom
void Client::_setCursor() {
    SDL_Surface *surface;
    SDL_Cursor *cursor;
    surface = SDL_LoadBMP(CURSOR_PATH);
    if (!surface) {
        throw TPException("Could not create cursor");
    }
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    SDL_FreeSurface(surface);
    if (!cursor) {
        throw TPException("Could not create cursor");
    }
    SDL_SetCursor(cursor);
}

void Client::_initializeSDL() {
    //Inicializa audio y video
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw TPException("Graphics could not initialize! Graphics Error: %s\n", SDL_GetError());
    } else {
        //Setea filtrado de texturas lineal
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "MipmapLinearNearest")) {
            std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        //Inicializa la carga de png
        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) & imgFlags)) {
            SDL_Quit();
            throw TPException("SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
        }
    }
    //Inicializa el reproductor de audio
    if(Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2, CHUNKSIZE) < 0) {
        IMG_Quit();
        SDL_Quit();
        throw TPException("SDL_mixer could not initialize!"
                          " SDL_mixer Error: %s\n", Mix_GetError());
    }
    //Inicializa el cargado de fonts para texto
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
