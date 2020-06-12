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

void Text::render(int x, int y){
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    textTexture.loadFromRenderedText(text, textColor, font.getFont());
    textTexture.renderText(x,y);
}

Text::~Text() {

}
