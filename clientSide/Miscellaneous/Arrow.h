//
// Created by marcos on 14/7/20.
//

#ifndef ARGENTUM_ARROW_H
#define ARGENTUM_ARROW_H

#include "../Texture/Texture.h"

class Arrow {
private:
    Texture& sTexture;
    SDL_Rect& camera;
    float angle, distance;
    float xPosition, width;
    float yPosition, height;
    bool finished{false};

public:
    Arrow(Texture& texture, SDL_Rect& camera, float x, float y,
                                             float xTarget, float yTarget);
    void render();
    bool finishedAnimation() const;
    void updatePosition(float x, float y);

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
    void _calculateTrajectory(float xTarget, float yTarget);
};


#endif //ARGENTUM_ARROW_H
