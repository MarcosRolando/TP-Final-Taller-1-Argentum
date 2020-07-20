//
// Created by ivan on 12/6/20.
//

#include "Text.h"

Text::Text(Font& font, SDL_Renderer& renderer, std::string&& _text) : font(font),
                                    textTexture(renderer) {
    text = std::move(_text);
    operator*();
}

Text& Text::updateText(std::string&& newText) {
    text = std::move(newText);
    return *this;
}

Text& Text::operator+=(std::string&& newText) {
    text += newText;
    return *this;
}

Text& Text::operator*(SDL_Color color) {
    if (!text.empty()) {
        textTexture.loadFromRenderedText(text, color, font.getFont());
    }
    return *this;
}

void Text::render(int x, int y) {
    if (!text.empty()) {
        textTexture.render(x, y);
    }
}

Text& Text::operator--() {
    if (!text.empty()) {
        text.pop_back();
    }
    return *this;
}

int Text::getTextLength() {
    return text.length();
}

std::string &Text::getText() {
    return text;
}

Text& Text::operator*() {
    return operator*({0xFF, 0xFF, 0xFF});
}

Text &Text::updateText(const std::string &newText) {
    text = newText;
    return *this;
}

Text::Text(Font& font, SDL_Renderer& renderer, const std::string& _text) : font(font),
                                                                      textTexture(renderer) {
    text = _text;
    operator*();
}

int Text::getTextTextureWidth() {
    if (!text.empty()) {
        return textTexture.getSpriteDimensions().width;
    } else {
        return 0;
    }
}

Text::Text(Text &&other) noexcept : font(other.font), text(std::move(other.text)),
                                    textTexture(std::move(other.textTexture)) {}

Text::~Text() = default;