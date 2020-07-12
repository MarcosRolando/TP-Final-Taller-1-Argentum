//
// Created by ivan on 23/6/20.
//

#include "MainMenu.h"
#include "../GameConstants.h"

#define START_GAME_BUTTON {50,100,135,25}
#define EXIT_BUTTON {50,875,90,25}

MainMenu::MainMenu(Texture& texture, Window& window) : window(window),
mainMenuFont("../SDL/Text/medieval.ttf", 25),
text(mainMenuFont, window.getRenderer()), mainMenuBackground(texture) {

    startGameButton.buttonEdges = START_GAME_BUTTON;
    exitButton.buttonEdges = EXIT_BUTTON;
    startGameButton.color = {0x00,0x00,0x00};
    exitButton.color = {0xFF,0xFF,0xFF};
}

void MainMenu::loop(bool& quit, std::string& _host,
                    std::string& _port, GameStartInfo& startInfo){
    SDL_Event e;
    bool inMainMenu = true;
    while (inMainMenu){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
                inMainMenu = false;
            }
            //Por si hago resize
            window.handleEvent(e);

            if (e.type == SDL_MOUSEMOTION){
                _handleMouseMotion();
            } else if (e.type == SDL_MOUSEBUTTONDOWN){
                _handleMouseButtonDown(inMainMenu, quit);
            }
        }
        _render();
    }
}

void MainMenu::_handleMouseMotion() {
    int x = 0, y = 0;
    SDL_GetMouseState( &x, &y );
    x = (float)x * ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
    y = (float)y * ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());

    //Seteo los colores default asi no quedan en rojo si pase el
    // mouse por encima
    startGameButton.color = {0x00,0x00,0x00};
    exitButton.color = {0xFF,0xFF,0xFF};
    if (_isInsideRect(x,y,startGameButton.buttonEdges)){
        startGameButton.color = {0xFF,0x00,0x00};
    } else if (_isInsideRect(x,y,exitButton.buttonEdges)){
        exitButton.color = {0xFF,0x00,0x00};
    }
}

void MainMenu::_handleMouseButtonDown(bool& inMainMenu, bool& quit) {
    int x = 0, y = 0;
    SDL_GetMouseState( &x, &y );
    x = (float)x * ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
    y = (float)y * ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());
    if (_isInsideRect(x,y,startGameButton.buttonEdges)){
        inMainMenu = false;
    } else if (_isInsideRect(x,y,exitButton.buttonEdges)){
        quit = true;
        inMainMenu = false;
    }
}

bool MainMenu::_isInsideRect(int x, int y, SDL_Rect rect){
    return ((x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y <
    rect.y + rect.h));
}

void MainMenu::_render(){
    window.clear();
    window.setViewport(ScreenViewport);
    mainMenuBackground.render(0,0);
    text.updateText("Start Game");
    text.render(50, 100, startGameButton.color);
    text.updateText("Exit");
    text.render(50, 875, exitButton.color);
    window.show();
}

MainMenu::~MainMenu(){}