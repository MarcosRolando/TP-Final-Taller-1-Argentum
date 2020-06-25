//
// Created by ivan on 18/6/20.
//

#include "Minichat.h"

#define MINICHAT_X_OFFSET 15
#define MINICHAT_Y_OFFSET 15

#define MAX_TEXT_LEN 93
#define MAX_MSGS 24 //El maximo de mensajes qu ese van a ver al scrollear
#define MAX_MSGS_TO_RENDER 8

Minichat::Minichat(SDL_Renderer& renderer) : minichatFont("../SDL/Text/font.ttf", 20),
                                input(minichatFont,renderer), renderer(renderer) {
    focusOnMinichat = false;
    input.updateText("Accion:/ ");//Pongo el Accion:/ aca xq me parece al
    // pedo crear un text solo para eso, pero capaz tengo q hacerlo por el
    // tema del protocolo

    //LLeno el vector con mensajes vacios
    for (int i = 0; i < MAX_MSGS; ++i) {
        texts.emplace_back(minichatFont,renderer);
    }
    firstToRender = 0;
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
    } else if (e.type == SDL_MOUSEWHEEL){
        if(e.wheel.y > 0) // scroll up
        {
            firstToRender += 1;
            if (firstToRender > MAX_MSGS - MAX_MSGS_TO_RENDER)
                firstToRender -= 1;
        }
        else if(e.wheel.y < 0) // scroll down
        {
            firstToRender -= 1;
            if (firstToRender < 0)
                firstToRender = 0;
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
        if (textNum >= firstToRender){
            text.render(0,140 - 20*(textNum - firstToRender), SDL_Color{0xFF,0xFF,0xFF,
                                                           0xFF});
        }
        textNum++;
        if (textNum >= MAX_MSGS_TO_RENDER + firstToRender) break;
    }
}

bool Minichat::_isInsideMinichat(int xClick, int yClick){
    return (xClick >= MINICHAT_X_OFFSET) &&
    (xClick < (MINICHAT_X_OFFSET + DEFAULT_MINICHAT_WIDTH))
    && ( yClick >= MINICHAT_Y_OFFSET )
    && ( yClick <= (MINICHAT_Y_OFFSET + DEFAULT_MINICHAT_HEIGHT));
}

Minichat::~Minichat() {}


