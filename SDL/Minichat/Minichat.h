//
// Created by ivan on 18/6/20.
//

#ifndef ARGENTUM_MINICHAT_H
#define ARGENTUM_MINICHAT_H

#include "../Text/Text.h"
#include "../../GameConstants.h"

class Minichat {
private:
    Text input;
    SDL_Renderer& renderer;
    SDL_Point mPosition;
    bool focusOnMinichat;
public:
    Minichat(Font& font, SDL_Renderer& renderer);
    void handleEvent( SDL_Event& e );
    ~Minichat();

    void render();

    void inputText(std::string &input);

    bool isFocused();
};


#endif //ARGENTUM_MINICHAT_H
