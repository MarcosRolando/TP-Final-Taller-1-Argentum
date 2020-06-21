//
// Created by ivan on 18/6/20.
//

#ifndef ARGENTUM_MINICHAT_H
#define ARGENTUM_MINICHAT_H

#include "../Text/Text.h"
#include "../../Screen/Window.h"
#include "../../GameConstants.h"
#include <list>
class Minichat {
private:
    Font& minichatFont;
    Text input;
    std::list<Text> texts;
    SDL_Renderer& renderer;
    SDL_Point mPosition;
    bool focusOnMinichat;
public:
    Minichat(Font& font, SDL_Renderer& renderer);
    void handleEvent( SDL_Event& e, Window& window);
    void render();
    ~Minichat();

    void queueText(std::string &newText);
};


#endif //ARGENTUM_MINICHAT_H
