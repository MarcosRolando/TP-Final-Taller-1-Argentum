//
// Created by ivan on 18/6/20.
//

#ifndef ARGENTUM_MINICHAT_H
#define ARGENTUM_MINICHAT_H

#include "../Text/Text.h"
#include "../../Screen/Window.h"
#include "../../Client/GameConstants.h"
#include <list>
#include "../../Map/Coordinate.h"
#include <mutex>

class Minichat {
private:
    Font minichatFont;
    Text input;
    std::list<Text> texts;
    SDL_Renderer& renderer;
    bool focusOnMinichat;
    int firstToRender;
    std::mutex generalMutex;
    std::mutex inputMutex;

public:
    explicit Minichat(SDL_Renderer& renderer);
    //Encola newText para imprimirlo en el minichat
    void queueText(std::string &newText);
    //Recibe texto y si es necesario lo separa en varias lineas del minichat
    void receiveText(const std::string &text);
    //Renderiza todos los mensajes del minichat + lo que escribio el usuario
    void render();
    //Borra la ultima letra del input
    void handleBackspace();
    //Asigna el texto del evento de input al texto de input del usuario
    void handleTextInput(SDL_Event &e);
    //Se fija si el click fue dentro del minichat. Si es asi habilita el input de texto
    void handleMouseButtonDown(Coordinate click, Window &window);
    //Scrollea por los mensajes del minichat
    void handleMouseWheel(SDL_Event &e);
    //Borra los mensajes del minichat
    void clearMinichat();
    /* Devuelve el input del usuario en el minichat para que sea parseado como comando */
    std::string handleReturnKey();
    /* Destructor */
    ~Minichat();

private:
    static bool _isInsideMinichat(int xClick, int yClick);

};

#endif //ARGENTUM_MINICHAT_H
