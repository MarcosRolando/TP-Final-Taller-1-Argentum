//
// Created by ivan on 23/6/20.
//

#include "MainMenu.h"
#include "../Client/GameConstants.h"
#include "../Client/GameInitializer.h"
#include "../../libs/Socket.h"

#define START_BUTTON {1375, 875, 100, 25}
#define CONNECT_BUTTON {1375, 875, 100, 25}
#define EXIT_BUTTON {50,875,90,25}

#define INPUT_HOST {115,100,200,25}
#define INPUT_PORT {115,200,200,25}
#define INPUT_NICKNAME {165,100,200,25}


#define LOAD_PLAYER_BUTTON {50,200,175,25}
#define CREATE_PLAYER_BUTTON {50,100,175,25}

#define MAX_TEXT_LEN 50


MainMenu::MainMenu(Texture& texture, Window& window) : window(window),
mainMenuFont("../../clientSide/Graphics/Text/medieval.ttf", 25),
text(mainMenuFont, window.getRenderer()),
hostInputText(mainMenuFont, window.getRenderer()),
portInputText(mainMenuFont, window.getRenderer()) ,
nicknameInputText(mainMenuFont, window.getRenderer()),
errorText(mainMenuFont, window.getRenderer()), mainMenuBackground(texture) {

    hostInput = false;
    portInput = false;
    nickInput = false;
    SDL_StartTextInput();
}


void MainMenu::connectLoop(bool& quit, std::string& _host,
                    std::string& _port, Socket& socket) {
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
                if (_isInsideRect(x,y,INPUT_HOST)) {
                    hostInput = true;
                    portInput = false;
                } else if (_isInsideRect(x,y,INPUT_PORT)) {
                    hostInput = false;
                    portInput = true;
                } else if (_isInsideRect(x,y,CONNECT_BUTTON)) {
                    _attemptToConnect(socket, finished);
                } else if (_isInsideRect(x,y,EXIT_BUTTON)) {
                    quit = true;
                    finished = true;
                }
            } else if (e.type == SDL_TEXTINPUT){
                _handleTextInput(e);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    _handleBackspace();
                }
            }
        }
        _renderConnectScreen();
    }
    hostInput = false;
    portInput = false;
    errorText.updateText("");
}

void MainMenu::playerSelectionLoop(bool& quit, GameInitializer& initializer, Socket& socket) {
    bool createPlayer = false;
    bool loadPlayer = false;
    bool success = false;

    while (!success && !quit) {
        playerSelection(quit, createPlayer, loadPlayer);//Veo si quiere hacer load o create
        if (!quit) {
            if (createPlayer) _createPlayer(quit, success, initializer, socket);
            else if (loadPlayer) _loadPlayer(quit, success, initializer, socket);

            if (success)
                break;
            else {
                bool reconnect = false;
                socket.close();
                _attemptToConnect(socket, reconnect);
                if (!reconnect) quit = true; //Aca seria q me cerraron el socket.
            }
        }
    }
}

void MainMenu::playerSelection(bool& quit, bool& createPlayer, bool& loadPlayer) {
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
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = 0, y = 0;
                SDL_GetMouseState(&x, &y);
                x = (float) x *
                    ((float) DEFAULT_SCREEN_WIDTH / (float) window.getWidth());
                y = (float) y * ((float) DEFAULT_SCREEN_HEIGHT /
                                 (float) window.getHeight());
                if (_isInsideRect(x, y, EXIT_BUTTON)) {
                    quit = true;
                    finished = true;
                } else if (_isInsideRect(x, y, CREATE_PLAYER_BUTTON)) {
                    createPlayer = true;
                    finished = true;
                } else if (_isInsideRect(x, y, LOAD_PLAYER_BUTTON)) {
                    loadPlayer = true;
                    finished = true;
                }
            }
        }
        _renderPlayerSelectionScreen();
    }
}

void MainMenu::_loadPlayer(bool &quit, bool &success, GameInitializer &initializer,
                           Socket &socket) {

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
                if (_isInsideRect(x,y,INPUT_NICKNAME)){
                    nickInput = true;
                } else if (_isInsideRect(x,y,EXIT_BUTTON)) {
                    quit = true;
                    finished = true;
                } else if (_isInsideRect(x,y,START_BUTTON)) {
                    if (!nicknameInputText.getText().empty()) {
                        _connectPlayer(initializer, socket, success);
                        finished = success;
                        if (!finished) return;//Xq si fallo la conexion el server me desconecta
                    }
                }
            } else if (e.type == SDL_TEXTINPUT){
                _handleTextInput(e);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    _handleBackspace();
                }
            }
        }
        _renderLoadPlayerScreen();
    }
}

void MainMenu::_createPlayer(bool &quit, bool &success, GameInitializer &initializer,
                             Socket &socket) {

}

void MainMenu::_connectPlayer(GameInitializer& initializer, Socket& socket, bool& success) {
        initializer.loadPlayer(nicknameInputText.getText());
        char serverAcceptedConnection;
        socket.receive(&serverAcceptedConnection, sizeof(serverAcceptedConnection));
        if (serverAcceptedConnection == 1)
            success = true;
        else {
            errorText.updateText("Player does not exist");
        }
}

void MainMenu::_attemptToConnect(Socket& socket, bool& finished) {
    try {
        socket.connect(hostInputText.getText(), portInputText.getText());
        finished = true;
    } catch (std::exception& e) {
        errorText.updateText("Could not connect");
    }
}

void MainMenu::_handleTextInput(SDL_Event& e) {
    std::string newInput = e.text.text;
    if (hostInput) {
        if (hostInputText.getTextLength() < MAX_TEXT_LEN)
            hostInputText.appendText(std::move(newInput));
    } else if (portInput) {
        if (portInputText.getTextLength() < MAX_TEXT_LEN)
            portInputText.appendText(std::move(newInput));
    } else if (nickInput) {
        if (nicknameInputText.getTextLength() < MAX_TEXT_LEN)
            nicknameInputText.appendText(std::move(newInput));
    }
}

void MainMenu::_handleBackspace() {
    if (hostInput) {
        hostInputText.eraseText();
    } else if (portInput) {
        portInputText.eraseText();
    } else if (nickInput) {
        nicknameInputText.eraseText();
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
    SDL_Rect outlineRect = INPUT_HOST;
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
    outlineRect = INPUT_PORT;
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );

    text.updateText("Host ");
    text.render(50, 100, {0x00,0x00,0x00});
    text.updateText("Port ");
    text.render(50, 200, {0x00,0x00,0x00});
    hostInputText.render(115, 100);
    portInputText.render(115, 200);
    errorText.render(650, 875, {0xff,0xff,0xff});
    text.updateText("Connect");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Exit");
    text.render(50, 875, {0xff,0xff,0xff});
    window.show();
}

void MainMenu::_renderPlayerSelectionScreen() {
    window.clear();
    window.setViewport(ScreenViewport);
    mainMenuBackground.render(0,0);
    text.updateText("Create Player");
    text.render(50, 100, {0x00,0x00,0x00});
    text.updateText("Load Player");
    text.render(50, 200, {0x00,0x00,0x00});
    text.updateText("Exit");
    text.render(50, 875, {0xff,0xff,0xff});
    errorText.render(650, 875, {0xff,0xff,0xff});
    window.show();
}

void MainMenu::_renderLoadPlayerScreen() {
    window.clear();
    window.setViewport(ScreenViewport);
    mainMenuBackground.render(0,0);
    SDL_Rect outlineRect = INPUT_NICKNAME;
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
    text.updateText("Nickname ");
    text.render(50, 100, {0x00,0x00,0x00});
    nicknameInputText.render(165, 100,{0x00,0x00,0x00});
    errorText.render(650, 875, {0xff,0xff,0xff});
    text.updateText("Start");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Exit");
    text.render(50, 875, {0xff,0xff,0xff});
    window.show();
}

MainMenu::~MainMenu(){
    SDL_StopTextInput();
}

