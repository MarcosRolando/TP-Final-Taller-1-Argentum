//
// Created by ivan on 12/6/20.
//

#include "Font.h"
#include "../../Texture/Texture.h"

#include <string>

#ifndef ARGENTUM_TEXT_H
#define ARGENTUM_TEXT_H


class Text {
private:
    Font& font;
    std::string text;
    Texture textTexture;

public:
    Text(Font& font, SDL_Renderer& renderer);

    void updateText(const std::string &newText);

    void appendText(const std::string &newText);

    void eraseText();

    int getTextLength();

    void render(int x, int y, SDL_Color color = {0, 0, 0});

    ~Text();
};


#endif //ARGENTUM_TEXT_H
