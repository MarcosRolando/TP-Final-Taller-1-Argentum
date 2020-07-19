//
// Created by marcos on 19/7/20.
//

#ifndef ARGENTUM_CAMERACOLLISIONVERIFIER_H
#define ARGENTUM_CAMERACOLLISIONVERIFIER_H

#include <SDL_rect.h>

class CameraCollisionVerifier {
public:
    static bool isInsideCamera(SDL_Rect a, SDL_Rect b, int adjustment);
    static bool isInsideCamera(SDL_Rect a, SDL_Rect b);
};


#endif //ARGENTUM_CAMERACOLLISIONVERIFIER_H
