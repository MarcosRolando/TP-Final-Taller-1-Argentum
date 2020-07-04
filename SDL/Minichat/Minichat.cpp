//
// Created by ivan on 18/6/20.
//

#include "Minichat.h"

#define MINICHAT_X_OFFSET 15
#define MINICHAT_Y_OFFSET 15

#define MAX_TEXT_LEN 94
#define MAX_MSGS 24 //El maximo de mensajes qu ese van a ver al scrollear
#define MAX_MSGS_TO_RENDER 8

Minichat::Minichat(SDL_Renderer& renderer) : minichatFont("../SDL/Text/font.ttf", 20),
                                input(minichatFont,renderer), renderer(renderer) {
    focusOnMinichat = false;
    input.updateText(":");//Pongo el Accion:/ aca xq me parece al
    // pedo crear un text solo para eso, pero capaz tengo q hacerlo por el
    // tema del protocolo

    //Lleno el vector con mensajes vacios
    for (int i = 0; i < MAX_MSGS; ++i) {
        texts.emplace_back(minichatFont,renderer);
    }
    firstToRender = 0;
}

//Ver esta funcion xq esta muy rancia
std::string Minichat::handleReturnKey() {
    std::string toPrint = input.getText();
    if (toPrint.size() > 1) {
        toPrint.erase(0, 1);//Le saco "Accion:"
        queueText(toPrint);//Imprimo el comando en el minichat
        input.updateText(":");
        return toPrint;
    }
    return " ";
}

void Minichat::handleBackspace() {
    if (input.getTextLength() > 1) {
        //Va un 9 asi no borro la parte fija que dice Accion
        //borro una letra
        input.eraseText();
    }
}

void Minichat::handleTextInput(SDL_Event &e) {
    std::string newInput = e.text.text;
    if (input.getTextLength() < MAX_TEXT_LEN) input.appendText(newInput);
}

void Minichat::handleMouseButtonDown(Coordinate click, Window& window) {
    focusOnMinichat = _isInsideMinichat(click.j, click.i);
    if (focusOnMinichat){
        SDL_StartTextInput();
    } else {
        SDL_StopTextInput();
    }
}

void Minichat::handleMouseWheel(SDL_Event& e){
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

void Minichat::receiveText(std::string& text) {
    //Separa un mensaje separado con \n en varias lineas
    int currPos = -1;
    int nextPos;
    while (currPos < (int)text.size()) {
        nextPos =  text.find('\n', currPos + 1);
        std::string substr = text.substr(currPos + 1, nextPos - currPos - 1);
        currPos = nextPos;
        if (substr.empty())
            break;

        queueText(substr);
    }
}

//Imprime los mensajes relevantes
void Minichat::queueText(std::string& newText) {
    if (!newText.empty()) {
        texts.pop_back();
        texts.emplace_front(minichatFont, renderer);
        texts.front().updateText(newText);
    }
}

void Minichat::render(){
    //renderizo input
    input.render(0,178, SDL_Color{0xFF,0xFF,0xFF,0xFF});
    //renderizo mensajes encolados. Prob haya una mejor forma de iterar esto
    int textNum = 0;
    for (auto & text : texts) {
        if (textNum >= firstToRender){
            if (!text.getText().empty()) {
                text.render(0,140 - 20*(textNum - firstToRender),
                            SDL_Color{0xFF,0xFF,0xFF,0xFF});
            }
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

Minichat::~Minichat() = default;


