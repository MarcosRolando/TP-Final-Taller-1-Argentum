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
    Font minichatFont;
    Text input;
    std::list<Text> texts;
    SDL_Renderer& renderer;
    bool focusOnMinichat;
    int firstToRender;

public:
    explicit Minichat(SDL_Renderer& renderer);
    void handleEvent( SDL_Event& e, Window& window);
    void queueText(std::string &newText);
    void render();
    ~Minichat();

    bool _isInsideMinichat(int xClick, int yClick);
};


#endif //ARGENTUM_MINICHAT_H
