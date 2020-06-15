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
    ~Text();

    void updateText(const std::string &newText);

    void render(int x, int y, SDL_Color color = {0, 0, 0});
};


#endif //ARGENTUM_TEXT_H
