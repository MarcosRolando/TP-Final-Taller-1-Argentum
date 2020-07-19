//
// Created by marcos on 6/13/20.
//

#ifndef ARGENTUM_SPELL_H
#define ARGENTUM_SPELL_H

#include "../Texture/Texture.h"

class Spell {
private:
    Texture& sTexture;
    SDL_Rect& camera;
    float timePassed;
    int currentFrame;
    float xPosition, width;
    float yPosition, height;
    bool finished{false};

public:
    Spell(Texture& texture, SDL_Rect& camera, float x, float y);

    /*Renderiza el hechizo (si fuera visible)*/
    void render();

    /*Actualiza el frame de la animacion del hechizo*/
    void updateFrame(double timeStep);

    /*Retorna true si el hechizo completo su animacion asi lo borro*/
    bool finishedAnimation() const;

    /*Cambia la posicion, lo utilizo para que vaya siguiendo al entity*/
    void setPosition(float x, float y);

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_SPELL_H
