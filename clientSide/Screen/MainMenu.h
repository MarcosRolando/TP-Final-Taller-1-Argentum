//
// Created by ivan on 23/6/20.
//

#ifndef ARGENTUM_MAINMENU_H
#define ARGENTUM_MAINMENU_H

#include "../Graphics/Text/Text.h"
#include "Window.h"
#include "../../libs/GameEnums.h"

class Socket;

struct GameStartInfo {
    bool createPlayer;
    std::string myNickname;
    GameType::Class myClass;
    GameType::Race myRace;
};

struct Button{
    SDL_Rect buttonEdges;
    SDL_Color color;
    bool available;
};

class MainMenu {
private:
    Window& window;
    Font mainMenuFont;
    Text text;
    Text hostInputText;
    Text portInputText;
    Text nicknameInputText;
    Texture& mainMenuBackground;
public:
    MainMenu(Texture& texture, Window& window);
    //void loop(bool& quit, std::string& _host,
      //        std::string& _port, GameStartInfo& startInfo);
    void connectLoop(bool &quit, std::string &_host, std::string &_port, Socket& socket);

    ~MainMenu();

private:
    bool _isInsideRect(int x, int y, SDL_Rect rect);

    void _render();

    void _handleMouseMotion();

    void _handleMouseButtonDown(bool &inMainMenu, bool &quit);

    void _renderConnectScreen();
};


#endif //ARGENTUM_MAINMENU_H
