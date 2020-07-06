//
// Created by ivan on 12/6/20.
//

#include "Text.h"

Text::Text(Font& font, SDL_Renderer& renderer) : font(font),
                                    textTexture(renderer) {
    text = " ";//Pongo esto xq SDL no puede renderizar texto vacio
}

void Text::updateText(std::string&& newText){
    text = std::move(newText);
}

void Text::appendText(std::string&& newText){
    text += newText;
}

void Text::render(int x, int y, SDL_Color color){
    textTexture.loadFromRenderedText(text, color, font.getFont());
    textTexture.renderText(x, y);
}

Text::~Text() = default;

void Text::eraseText() {
    text.pop_back();
}

int Text::getTextLength() {
    return text.length();
}

std::string &Text::getText() {
    return text;
}



