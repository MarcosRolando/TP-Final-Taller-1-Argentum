//
// Created by marcos on 6/13/20.
//

#ifndef ARGENTUM_SPELL_H
#define ARGENTUM_SPELL_H

#include "../Texture/Texture.h"
#include <vector>

class Spell {
private:
    Texture& sTexture;
    SDL_Rect& camera;
    float timePassed;
    int currentFrame;
    float xPosition, width;
    float yPosition, height;

public:
    Spell(Texture& texture, SDL_Rect& camera, float x, float y);
    void render(float timeStep);

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
    void _updateFrame(float stepTime);
};


#endif //ARGENTUM_SPELL_H
