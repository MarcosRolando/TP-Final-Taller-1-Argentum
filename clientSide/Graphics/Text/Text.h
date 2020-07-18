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
    /* Constructor */
    Text(Font& font, SDL_Renderer& renderer);
    /* Setea el texto a "newText" */
    void updateText(std::string&& newText);
    /* Agrega "newText" al final del texto */
    void appendText(std::string&& newText);
    /* Borra la ultima letra del texto */
    void eraseText();
    /* Me devuelve el tamaño del texto */
    int getTextLength();
    /* Me devuelve una referencia al texto */
    std::string& getText();
    /* Renderiza el texto en la posicion (x,y) con el color "color" */
    void render(int x, int y, SDL_Color color = {0, 0, 0});
    /* Destructor */
    ~Text();
};


#endif //ARGENTUM_TEXT_H
