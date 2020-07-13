//
// Created by ivan on 23/6/20.
//

#include "MainMenu.h"
#include "../Client/GameConstants.h"
#include "../../libs/Socket.h"

#define START_GAME_BUTTON {50,100,135,25}
#define CONNECT_BUTTON {1375, 875, 100, 25}
#define EXIT_BUTTON {50,875,90,25}

#define INPUT_HOST {100,100,200,25}
#define INPUT_PORT {100,200,200,25}

#define MAX_TEXT_LEN 50


MainMenu::MainMenu(Texture& texture, Window& window) : window(window),
mainMenuFont("../../clientSide/Graphics/Text/medieval.ttf", 25),
text(mainMenuFont, window.getRenderer()),
hostInputText(mainMenuFont, window.getRenderer()),
portInputText(mainMenuFont, window.getRenderer()) ,
nicknameInputText(mainMenuFont, window.getRenderer()), mainMenuBackground(texture) {

}

/*void MainMenu::loop(bool& quit, std::string& _host,
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
}*/

void MainMenu::connectLoop(bool& quit, std::string& _host,
                    std::string& _port, Socket& socket) {
    bool inputHost = false;//Estos bools estan para ver donde escribir el input
    bool inputPort = false;
    bool finished = false;
    SDL_Event e;
    while (!finished){
        while (SDL_PollEvent(&e) != 0){
            if (e.type == SDL_QUIT){
                quit = true;
                finished = true;
            }
            //Por si hago resize
            window.handleEvent(e);
            if (e.type == SDL_MOUSEBUTTONDOWN){
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                x = (float)x * ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
                y = (float)y * ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());
                if (_isInsideRect(x,y,INPUT_HOST)){
                    inputHost = true;
                    inputPort = false;
                } else if (_isInsideRect(x,y,INPUT_PORT)) {
                    inputHost = false;
                    inputPort = true;
                } else if (_isInsideRect(x,y,CONNECT_BUTTON)) {
                    try {
                        socket.connect(hostInputText.getText(), portInputText.getText());
                        finished = true;
                    } catch (std::exception& e) {
                    }
                } else if (_isInsideRect(x,y,EXIT_BUTTON)) {
                    quit = true;
                    finished = true;
                }
            } else if (e.type == SDL_TEXTINPUT){
                std::string newInput = e.text.text;
                if (inputHost) {
                    if (hostInputText.getTextLength() < MAX_TEXT_LEN)
                        hostInputText.appendText(std::move(newInput));
                } else if (inputPort) {
                    if (portInputText.getTextLength() < MAX_TEXT_LEN)
                        portInputText.appendText(std::move(newInput));
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (inputHost) {
                        hostInputText.eraseText();
                    } else if (inputPort) {
                        portInputText.eraseText();
                    }
                }
            }
        }
        _renderConnectScreen();
    }
}

bool MainMenu::_isInsideRect(int x, int y, SDL_Rect rect){
    return ((x > rect.x) && (x < rect.x + rect.w) && (y > rect.y) && (y <
    rect.y + rect.h));
}

void MainMenu::_renderConnectScreen(){
    window.clear();
    window.setViewport(ScreenViewport);
    mainMenuBackground.render(0,0);

    text.updateText("Host: ");
    text.render(50, 100, {0x00,0x00,0x00});
    text.updateText("Port: ");
    text.render(50, 200, {0x00,0x00,0x00});

    hostInputText.render(115, 100);
    portInputText.render(115, 200);

    text.updateText("Connect");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Exit");
    text.render(50, 875, {0xff,0xff,0xff});
    window.show();
}

MainMenu::~MainMenu(){}