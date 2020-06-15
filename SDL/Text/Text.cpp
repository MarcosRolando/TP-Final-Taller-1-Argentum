//
// Created by ivan on 12/6/20.
//

#include "Text.h"

Text::Text(Font& font, SDL_Renderer& renderer) : font(font),
                                    textTexture(renderer) {
}

void Text::updateText(const std::string& newText){
    text = newText;
}

void Text::render(int x, int y, SDL_Color color){
    textTexture.loadFromRenderedText(text, color, font.getFont());
    textTexture.renderText(x, y);
}

Text::~Text() {

}