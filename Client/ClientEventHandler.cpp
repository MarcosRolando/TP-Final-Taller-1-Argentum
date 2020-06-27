//
// Created by ivan on 26/6/20.
//

#include "ClientEventHandler.h"

void ClientEventHandler::run() {
    SDL_Event e;
    Window& window = game.getWindow();
    Minichat& minichat = game.getMinichat();
    Selector& selector = game.getSelector();
    int xPlayer, yPlayer;
    //While application is running
    while (!quit) {
        //Esto capaz lo cambiamos de lugar despues
        xPlayer = game.getPlayerInfo().getXPos();
        yPlayer = game.getPlayerInfo().getYPos();
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            selector.handleEvent(e, xPlayer, yPlayer, window);
            minichat.handleEvent(e, game.getWindow());
            window.handleEvent(e);

            //std::string a = " ";//Para probar lo del minichat

           /*if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        a = "up";
                        minichat.queueText(a);
                        player.move(UP);
                        break;
                    case SDLK_DOWN:
                        a = "down";
                        minichat.queueText(a);
                        player.move(DOWN);
                        break;
                    case SDLK_LEFT:
                        a = "left";
                        minichat.queueText(a);
                        player.move(LEFT);
                        break;
                    case SDLK_RIGHT:
                        a = "right";
                        minichat.queueText(a);
                        player.move(RIGHT);
                        break;
                    case SDLK_SPACE://Esto es para probar pausar la musica
                        if (!soundPlayer.isMusicPlaying()) {
                            soundPlayer.pauseMusic();
                        } else {
                            soundPlayer.playMusic();
                        }
                        break;
                }
            }*/
        }
    }
}

ClientEventHandler::~ClientEventHandler() {

}
