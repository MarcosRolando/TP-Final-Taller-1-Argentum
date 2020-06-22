//
// Created by ivan on 18/6/20.
//

#include "Minichat.h"

#define MINICHAT_X_OFFSET 15
#define MINICHAT_Y_OFFSET 15

#define MAX_TEXT_LEN 93
#define MAX_MSGS 7

Minichat::Minichat(Font& font, SDL_Renderer& renderer) : minichatFont(font),
input(font,renderer), renderer(renderer) {
    focusOnMinichat = false;
    input.updateText("Accion:/ ");//Pongo el Accion:/ aca xq me parece al
    // pedo crear un text solo para eso, pero capaz tengo q hacerlo por el
    // tema del protocolo

    //LLeno el vector con mensajes vacios
    for (int i = 0; i < MAX_MSGS; ++i) {
        texts.emplace_back(font,renderer);
    }
}

void Minichat::handleEvent(SDL_Event &e, Window& window) {
    //If mouse event happened

    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        int x = 0, y = 0;
        //Get mouse position
        //int x, y;
        SDL_GetMouseState( &x, &y );
        //Chequeo si hizo click en el minichat
        //Escalo la posicion del click por si cambia el tamaño de la pantalla
        x = (float)x * ((float)DEFAULT_SCREEN_WIDTH/(float)window.getWidth());
        y = (float)y * ((float)DEFAULT_SCREEN_HEIGHT/(float)window.getHeight());

        focusOnMinichat = _isInsideMinichat(x, y);

        if (focusOnMinichat){
            SDL_StartTextInput();
        }

    } else if( e.type == SDL_TEXTINPUT ) {
            std::string newInput = e.text.text;
            if (input.getTextLength() < MAX_TEXT_LEN) input.appendText(newInput);
    } else if( e.type == SDL_KEYDOWN ) {
        if (e.key.keysym.sym == SDLK_BACKSPACE && input.getTextLength() > 8) {
            //Va un 8 asi no borro la parte fija que dice Accion

            //borro letra
            input.eraseText();
        } else if (e.key.keysym.sym == SDLK_RETURN){
            //Procesar el comando que escribio el user
            input.updateText("Accion:/ ");
        }
    }
    if (!focusOnMinichat){
        SDL_StopTextInput();
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
    //renderizo mensajes encolados. Prob haya una mejor forma de iterar esto
    int textNum = 0;
    for (auto & text : texts) {
        text.render(0,140 - 20*textNum, SDL_Color{0xFF,0xFF,0xFF,0xFF});
        textNum++;
    }
}

bool Minichat::_isInsideMinichat(int xClick, int yClick){
    return (xClick >= MINICHAT_X_OFFSET) &&
    (xClick < (MINICHAT_X_OFFSET + DEFAULT_MINICHAT_WIDTH))
    && ( yClick >= MINICHAT_Y_OFFSET )
    && ( yClick <= (MINICHAT_Y_OFFSET + DEFAULT_MINICHAT_HEIGHT));
}

Minichat::~Minichat() {}


