//
// Created by ivan on 23/6/20.
//

#ifndef ARGENTUM_MAINMENU_H
#define ARGENTUM_MAINMENU_H

#include "../SDL/Text/Text.h"
#include "Window.h"

struct Button{
    SDL_Rect buttonEdges;
    SDL_Color color;
};

class MainMenu {
private:
    Window& window;
    Text text;
    Texture& mainMenuBackground;
    Button startGameButton{};
    Button exitButton{};
public:
    MainMenu(Texture& texture, Window& window, Font& font);
    void loop(bool& quit);
    ~MainMenu();

private:
    bool _isInsideRect(int x, int y, SDL_Rect rect);

    void _render();
};


#endif //ARGENTUM_MAINMENU_H
