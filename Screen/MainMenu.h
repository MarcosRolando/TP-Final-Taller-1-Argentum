//
// Created by ivan on 23/6/20.
//

#ifndef ARGENTUM_MAINMENU_H
#define ARGENTUM_MAINMENU_H

#include "../SDL/Text/Text.h"
#include "Window.h"
#include "../Shared/GameEnums.h"

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
    Text inputText;
    Texture& mainMenuBackground;
    Button startGameButton{};
    Button exitButton{};
public:
    MainMenu(Texture& texture, Window& window);
    void loop(bool& quit, std::string& _host,
              std::string& _port, GameStartInfo& startInfo);
    void connectLoop(bool &quit, std::string &_host, std::string &_port);

    ~MainMenu();

private:
    bool _isInsideRect(int x, int y, SDL_Rect rect);

    void _render();

    void _handleMouseMotion();

    void _handleMouseButtonDown(bool &inMainMenu, bool &quit);

};


#endif //ARGENTUM_MAINMENU_H
