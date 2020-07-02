//
// Created by ivan on 18/6/20.
//

#ifndef ARGENTUM_MINICHAT_H
#define ARGENTUM_MINICHAT_H

#include "../Text/Text.h"
#include "../../Screen/Window.h"
#include "../../GameConstants.h"
#include <list>
#include "../../Map/Coordinate.h"

class Minichat {
private:
    Font minichatFont;
    Text input;
    std::list<Text> texts;
    SDL_Renderer& renderer;
    bool focusOnMinichat;
    int firstToRender;

public:
    explicit Minichat(SDL_Renderer& renderer);
    void handleEvent( SDL_Event& e, Window& window);
    //Encola newText para imprimirlo en el minichat
    void queueText(std::string &newText);
    //Renderiza todos los mensajes del minichat + lo q escribio el usuario
    void render();
    //Borra la ultima letra del input
    void handleBackspace();
    //Asigna el texto del evento de input al texto de input del usuario
    void handleTextInput(SDL_Event &e);
    //Se fija si el click fue dentro del minichat. Si es asi habilita el input de texto
    void handleMouseButtonDown(Coordinate click, Window &window);
    //Scrollea por los mensajes del minichat
    void handleMouseWheel(SDL_Event &e);
    //todo retorna el mensaje de input para parsearlo y enviarlo
    void handleReturnKey();
    ~Minichat();

private:
    bool _isInsideMinichat(int xClick, int yClick);
};

#endif //ARGENTUM_MINICHAT_H
