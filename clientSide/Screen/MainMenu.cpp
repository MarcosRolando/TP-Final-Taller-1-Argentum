//
// Created by ivan on 23/6/20.
//

#include "MainMenu.h"
#include "../Client/GameConstants.h"
#include "../Client/GameInitializer.h"
#include "../../libs/Socket.h"
#include <netdb.h>

#define START_BUTTON {1375, 875, 100, 25}
#define CONNECT_BUTTON {1375, 875, 100, 25}
#define EXIT_BUTTON {50,875,90,25}
#define BACK_BUTTON {50,875,90,25}


#define INPUT_HOST {115,100,365,25}
#define INPUT_PORT {115,200,365,25}
#define INPUT_NICKNAME {165,100,365,25}

#define WARRIOR_BUTTON {150, 200, 100, 25}
#define WIZARD_BUTTON {300, 200, 100, 25}
#define CLERIC_BUTTON {450, 200, 100, 25}
#define PALADIN_BUTTON {600, 200, 100, 25}

#define HUMAN_BUTTON {150, 300, 100, 25}
#define ELF_BUTTON {300, 300, 100, 25}
#define DWARF_BUTTON {450, 300, 100, 25}
#define GNOME_BUTTON {600, 300, 100, 25}

#define LOAD_PLAYER_BUTTON {50,200,175,25}
#define CREATE_PLAYER_BUTTON {50,100,175,25}

#define MAX_TEXT_LEN 25


MainMenu::MainMenu(Texture& texture, Window& window) : window(window),
mainMenuFont("../../clientSide/Graphics/Text/medieval.ttf", 25),
text(mainMenuFont, window.getRenderer()),
hostInputText(mainMenuFont, window.getRenderer()),
portInputText(mainMenuFont, window.getRenderer()) ,
nicknameInputText(mainMenuFont, window.getRenderer()),
errorText(mainMenuFont, window.getRenderer()),
strength(mainMenuFont, window.getRenderer()),
constitution(mainMenuFont, window.getRenderer()),
intelligence(mainMenuFont, window.getRenderer()),
agility(mainMenuFont, window.getRenderer()),
mainMenuBackground(texture) {

    hostInput = false;
    portInput = false;
    nickInput = false;
    SDL_StartTextInput();
    info = {GameType::WARRIOR, GameType::HUMAN};
}

void MainMenu::menuScreen(bool& quit, GameInitializer& initializer, Socket& socket) {
    bool createPlayer = false;
    bool loadPlayer = false;
    bool success = false;
    bool goBack;

    while (!success && !quit) {
        _playerSelectionScreen(quit, createPlayer, loadPlayer);//Veo si quiere hacer load o create
        if (createPlayer) {
            do {
                goBack = false;
                _playerCreationScreen(quit, goBack);
                if (goBack) break;
                _connectScreen(quit, goBack, socket);
                if (!quit && !goBack)//xq puedo hacer quit en el connect
                    _connectCreatedPlayer(initializer, socket, success);
            } while (goBack);
        } else if (loadPlayer) {
            do {
                goBack = false;
                _playerLoadScreen(quit, goBack);
                if (goBack) break;
                _connectScreen(quit, goBack, socket);
                if (!quit && !goBack)//xq puedo hacer quit en el connect
                    _connectLoadedPlayer(initializer, socket, success);
            } while (goBack);
        }
        if (!success && !goBack) {
            socket.close();
        }
    }
}

void MainMenu::_connectScreen(bool& quit, bool& goBack, Socket& socket) {
    bool finished = quit;
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
                } else if (_isInsideRect(x,y,BACK_BUTTON)) {
                    goBack = true;
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

void MainMenu::_playerSelectionScreen(bool& quit, bool& createPlayer, bool& loadPlayer) {
    bool finished = quit;
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
                    loadPlayer = false;
                    finished = true;
                } else if (_isInsideRect(x, y, LOAD_PLAYER_BUTTON)) {
                    loadPlayer = true;
                    createPlayer = false;
                    finished = true;
                }
            }
        }
        _renderPlayerSelectionScreen();
    }
}

void MainMenu::_playerLoadScreen(bool &quit, bool& goBack) {
    errorText.updateText("");
    bool finished = quit;
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
                } else if (_isInsideRect(x,y,BACK_BUTTON)) {
                    goBack = true;
                    finished = true;
                } else if (_isInsideRect(x,y,START_BUTTON)) {
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
        _renderLoadPlayerScreen();
    }
    nickInput = false;
}

void MainMenu::_playerCreationScreen(bool &quit, bool &goBack) {
    errorText.updateText("");
    bool finished = quit;
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
                } else if (_isInsideRect(x,y,BACK_BUTTON)) {
                    goBack = true;
                    finished = true;
                } else if (_isInsideRect(x,y,START_BUTTON)) {
                   finished = true;
                } else {
                    _verifyClassSelection(x, y);
                    _verifyRaceSelection(x, y);
                }
            } else if (e.type == SDL_TEXTINPUT){
                _handleTextInput(e);
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    _handleBackspace();
                }
            }
        }
        _renderCreatePlayerScreen();
    }
    nickInput = false;
}

void MainMenu::_verifyClassSelection(int x, int y){
    if (_isInsideRect(x,y,WARRIOR_BUTTON)) info.myClass = GameType::WARRIOR;
    else if (_isInsideRect(x,y,WIZARD_BUTTON)) info.myClass = GameType::WIZARD;
    else if (_isInsideRect(x,y,CLERIC_BUTTON)) info.myClass = GameType::CLERIC;
    else if (_isInsideRect(x,y,PALADIN_BUTTON)) info.myClass = GameType::PALADIN;
}

void MainMenu::_verifyRaceSelection(int x, int y) {
    if (_isInsideRect(x,y,HUMAN_BUTTON)) info.myRace = GameType::HUMAN;
    else if (_isInsideRect(x,y,ELF_BUTTON)) info.myRace = GameType::ELF;
    else if (_isInsideRect(x,y,DWARF_BUTTON)) info.myRace = GameType::DWARF;
    else if (_isInsideRect(x,y,GNOME_BUTTON)) info.myRace = GameType::GNOME;
}

void MainMenu::_connectCreatedPlayer(GameInitializer& initializer, Socket& socket, bool& success) {
    if (nicknameInputText.getText().find(' ') != std::string::npos) {
        errorText.updateText("Nickname can not contain spaces");
        return;
    }
    if (!nicknameInputText.getText().empty()) {
        initializer.loadPlayer(nicknameInputText.getText(), info.myRace, info.myClass);
        GameType::ConnectionResponse response{};
        socket.receive(reinterpret_cast<char*>(&response), sizeof(response));
        response = static_cast<GameType::ConnectionResponse>(ntohl(response));
        switch (response) {
            case GameType::ACCEPTED:
                success = true;
                break;
            case GameType::UNAVAILABLE_PLAYER:
                errorText.updateText("Nickname " + nicknameInputText.getText() +
                                                                " is already in use");
                break;
            case GameType::UNKOWN_SERVER_ERROR:
                errorText.updateText("Unknown Server Error");
                break;
            default:
                errorText.updateText("Unknown Error");
                break;
        }
    }
}

void MainMenu::_connectLoadedPlayer(GameInitializer& initializer, Socket& socket, bool& success) {
    if (!nicknameInputText.getText().empty()) {
        initializer.loadPlayer(nicknameInputText.getText());
        GameType::ConnectionResponse response{};
        socket.receive(reinterpret_cast<char*>(&response), sizeof(int32_t));
        response = static_cast<GameType::ConnectionResponse>(ntohl(response));
        switch (response) {
            case GameType::ACCEPTED:
                success = true;
                break;
            case GameType::INEXISTENT_PLAYER:
                errorText.updateText("Player " + nicknameInputText.getText()
                                                                + " does not exist");
                break;
            case GameType::UNKOWN_SERVER_ERROR:
                errorText.updateText("Unknown Server Error");
                break;
            default:
                errorText.updateText("Unknown Error");
                break;
        }
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

    text.updateText("Host: ");
    text.render(50, 100, {0x00,0x00,0x00});
    text.updateText("Port: ");
    text.render(50, 200, {0x00,0x00,0x00});
    hostInputText.render(115, 100);
    portInputText.render(115, 200);
    errorText.render(650, 875, {0xff,0xff,0xff});
    text.updateText("Connect");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Back");
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
    text.updateText("Nickname: ");
    text.render(50, 100, {0x00,0x00,0x00});
    nicknameInputText.render(165, 100,{0x00,0x00,0x00});
    errorText.render(650, 875, {0xff,0xff,0xff});
    text.updateText("Start");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Back");
    text.render(50, 875, {0xff,0xff,0xff});
    window.show();
}

void MainMenu::_renderCreatePlayerScreen() {
    window.clear();
    window.setViewport(ScreenViewport);
    mainMenuBackground.render(0,0);
    SDL_Rect outlineRect = INPUT_NICKNAME;
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
    text.updateText("Nickname: ");
    text.render(50, 100, {0x00,0x00,0x00});

    strength.updateText("Strength");
    constitution.updateText("Constitution");
    intelligence.updateText("Intelligence");
    agility.updateText("Agility");
    _renderClass();
    _renderRace();
    strength.render(50, 400, {0x00,0x00,0x00});
    constitution.render(50, 500, {0x00,0x00,0x00});
    intelligence.render(50, 600, {0x00,0x00,0x00});
    agility.render(50, 700, {0x00,0x00,0x00});

    nicknameInputText.render(165, 100,{0x00,0x00,0x00});
    errorText.render(650, 875, {0xff,0xff,0xff});

    text.updateText("Start");
    text.render(1375, 875, {0xff,0xff,0xff});
    text.updateText("Back");
    text.render(50, 875, {0xff,0xff,0xff});
    window.show();
}

void MainMenu::_renderClass() {
    text.updateText("Class: ");
    text.render(50, 200, {0x00,0x00,0x00});
    text.updateText("Warrior");
    text.render(150, 200, {0x00,0x00,0x00});
    text.updateText("Wizard");
    text.render(300, 200, {0x00,0x00,0x00});
    text.updateText("Cleric");
    text.render(450, 200, {0x00,0x00,0x00});
    text.updateText("Paladin");
    text.render(600, 200, {0x00,0x00,0x00});

    SDL_Rect outlineRect;
    switch (info.myClass) {
        case GameType::WARRIOR:
            outlineRect = WARRIOR_BUTTON;
            _updateWarriorSkills();
            break;
        case GameType::WIZARD:
            outlineRect = WIZARD_BUTTON;
            _updateWizardSkills();
            break;
        case GameType::CLERIC:
            outlineRect = CLERIC_BUTTON;
            _updateClericSkills();
            break;
        case GameType::PALADIN:
            outlineRect = PALADIN_BUTTON;
            _updatePaladinSkills();
            break;
    }
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
}

void MainMenu::_renderRace() {
    text.updateText("Race: ");
    text.render(50, 300, {0x00,0x00,0x00});
    text.updateText("Human");
    text.render(150, 300, {0x00,0x00,0x00});
    text.updateText("Elf");
    text.render(300, 300, {0x00,0x00,0x00});
    text.updateText("Dwarf");
    text.render(450, 300, {0x00,0x00,0x00});
    text.updateText("Gnome");
    text.render(600, 300, {0x00,0x00,0x00});
    SDL_Rect outlineRect;
    switch (info.myRace) {
        case GameType::HUMAN:
            outlineRect = HUMAN_BUTTON;
            _updateHumanSkills();
            break;
        case GameType::ELF:
            outlineRect = ELF_BUTTON;
            _updateElfSkills();
            break;
        case GameType::DWARF:
            outlineRect = DWARF_BUTTON;
            _updateDwarfSkills();
            break;
        case GameType::GNOME:
            outlineRect = GNOME_BUTTON;
            _updateGnomeSkills();
            break;
    }
    SDL_SetRenderDrawColor(&window.getRenderer(), 0x3f, 0x2a,
                           0x14, 0xFF);
    SDL_RenderDrawRect( &window.getRenderer(), &outlineRect );
}

void MainMenu::_updateWarriorSkills() {
    strength.appendText("++++");
    constitution.appendText("+++");
    intelligence.appendText("");
    agility.appendText("");
}

void MainMenu::_updateWizardSkills() {
    strength.appendText("");
    constitution.appendText("");
    intelligence.appendText("+++++");
    agility.appendText("");
}

void MainMenu::_updateClericSkills() {
    strength.appendText("++");
    constitution.appendText("++");
    intelligence.appendText("+++");
    agility.appendText("");
}

void MainMenu::_updatePaladinSkills() {
    strength.appendText("+++");
    constitution.appendText("+++");
    intelligence.appendText("+");
    agility.appendText("");
}

void MainMenu::_updateHumanSkills() {
    strength.appendText("++");
    constitution.appendText("++");
    intelligence.appendText("++");
    agility.appendText("++");
}

void MainMenu::_updateElfSkills() {
    strength.appendText("");
    constitution.appendText("");
    intelligence.appendText("++++");
    agility.appendText("+++");
}

void MainMenu::_updateDwarfSkills() {
    strength.appendText("++++");
    constitution.appendText("+++");
    intelligence.appendText("");
    agility.appendText("");
}

void MainMenu::_updateGnomeSkills() {
    strength.appendText("++");
    constitution.appendText("+++");
    intelligence.appendText("++");
    agility.appendText("");
}

MainMenu::~MainMenu(){
    SDL_StopTextInput();
}