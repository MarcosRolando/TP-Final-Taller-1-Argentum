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
    Text(Font& font, SDL_Renderer& renderer, std::string&& _text = "");

    Text(Font& font, SDL_Renderer& renderer, const std::string& _text);

    Text(Text&& other) noexcept;

    /* Setea el texto a "newText" */
    Text& updateText(std::string&& newText);

    /* Setea el texto a "newText" */
    Text& updateText(const std::string& newText);

    /* Agrega "newText" al final del texto */
    Text& operator+=(std::string&& newText);

    /* Borra la ultima letra del texto */
    Text& operator--();

    /* Me devuelve el tamaño del texto */
    int getTextLength();

    /* Me devuelve una referencia al texto */
    std::string& getText();

    /* Renderiza el texto en la posicion (x,y) con el color "color" */
    void render(int x, int y);

    /* Genera la textura en base al texto almacendo */
    Text& operator*(SDL_Color color);

    /* Es para mandarle un color default al otro, C++ no me deja ponerle default sino*/
    Text& operator*();

    /*Retorna el ancho en pixeles del texto, se usa para dejar lindo el nombre con el nivel*/
    int getTextTextureWidth();

    ~Text();
};


#endif //ARGENTUM_TEXT_H
