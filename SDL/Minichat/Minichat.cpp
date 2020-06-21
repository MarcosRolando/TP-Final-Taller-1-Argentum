//
// Created by ivan on 18/6/20.
//

#include "Minichat.h"

#define MAX_TEXT_LEN 93

Minichat::Minichat(Font& font, SDL_Renderer& renderer) : minichatFont(font),
input(font,renderer), renderer(renderer) {
    focusOnMinichat = false;
    mPosition.x = 15; //Pos de inicio del viewport del minichat
    mPosition.y = 15;
    input.updateText("Accion:/ ");//Pongo el Accion:/ aca xq me parece al
    // pedo crear un text solo para eso, pero capaz tengo q hacerlo por el
    // tema del protocolo
    //LLeno el vector con mensajes vacios
    for (int i = 0; i < 7; ++i) {
        texts.emplace_back(font,renderer);
    }
}

void Minichat::handleEvent(SDL_Event &e, Window& window) {
    //If mouse event happened
    int x = 0, y = 0;
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        //Get mouse position
        //int x, y;
        SDL_GetMouseState( &x, &y );
        //Chequeo si hizo click en el minichat
        //Esto rompe en pantalla completa. Ver con marcos como hacer
        x = (float)x * ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
        y = (float)y * ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());

        focusOnMinichat = x >= mPosition.x && ( (float)x < (float)(mPosition.x +
                DEFAULT_MINICHAT_WIDTH) ) && ( y >= mPosition.y )
                        && ( y <= (mPosition.y + DEFAULT_MINICHAT_HEIGHT));



    } else if( e.type == SDL_TEXTINPUT ) {
        if (focusOnMinichat){
            std::string newInput = e.text.text;
            if (input.getTextLength() < MAX_TEXT_LEN)
                input.appendText(newInput);
        }
    } else if( e.type == SDL_KEYDOWN ) {
        if (e.key.keysym.sym == SDLK_BACKSPACE && input.getTextLength() > 8
        && focusOnMinichat) {//Va un 8 asi no borro la parte fija que dice
            // Accion

            //borro letra
            input.eraseText();
        } else if (e.key.keysym.sym == SDLK_RETURN && focusOnMinichat ){
            input.updateText("Accion:/ ");
            //Procesar el comando que escribio el user
        }
    }
}

//Imprime los mensajes relevantes
void Minichat::queueText(std::string& newText){
    texts.pop_back();
    texts.emplace_front(minichatFont, renderer);
    texts.front().updateText(newText);
}

void Minichat::render(){
    //renderizo input
    input.render(0,178, SDL_Color{0xFF,0xFF,0xFF,0xFF});
    //renderizo mensajes encolados
    int textNum = 0;
    for (auto & text : texts) {
        text.render(0,140 - 20*textNum, SDL_Color{0xFF,0xFF,0xFF,0xFF});
        textNum++;
    }
}

Minichat::~Minichat() {}


