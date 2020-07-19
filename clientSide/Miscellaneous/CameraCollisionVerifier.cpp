//
// Created by marcos on 19/7/20.
//

#include "CameraCollisionVerifier.h"

/*Verifica si el se encuentra adentro de la camara (para renderizarlo solo
 * si hace falta). Adjustment es para las estructuras ya que ocupan mas de un
 * tile y las dimensiones son ligeramentes distintas*/

/*Este se usa para las estructuras*/
bool CameraCollisionVerifier::isInsideCamera(SDL_Rect a, SDL_Rect b, int adjustment) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Calculo los lados de A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculo los lados de B
    leftB = b.x;
    rightB = b.x + b.w + adjustment;
    topB = b.y  + adjustment - b.h;
    bottomB = b.y + adjustment; /*Porque centro las estructuras en el medio del tile*/

    //Si alguno de los lados de A esta fuera de B
    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    //Si ningun lado de A esta fuera de B
    return true;
}

/*Este se usa para las que no son estructuras*/
bool CameraCollisionVerifier::isInsideCamera(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    //Calculo los lados de A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculo los lados de A
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    return true;
}
