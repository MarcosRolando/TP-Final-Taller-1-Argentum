//
// Created by marcos on 6/9/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H

#include "../Texture/EntityTexture.h"
#include "../Shared/GameEnums.h"
#include <list>

/*Clase Abstracta*/

class Entity {
private:
    SDL_Rect& camera;
    int currentFrame;
    GameType::Direction moveDirection, lastDirection;
    float xPosition, width;
    float yPosition, height;
    float distanceToMove{0}, distancePerMilisecond{0}; /*Se mide en pixeles*/
    float currentDistanceMoved{0}, totalDistanceMoved{0};

public:
    Entity(SDL_Rect& camera, float x, float y);
    void move(GameType::Direction direction, unsigned int distanceTravelled,
              std::list<Entity *> &movingEntities);
    void render(EntityTexture& eTexture);
    virtual void render() = 0;
    void updatePosition(float stepTime);
    void updateCamera();

    bool finishedMoving() const;

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
    void _renderLastDirection(EntityTexture& eTexture);
    void _modifyPosition(GameType::Direction direction, float distance);
};


#endif //ARGENTUM_ENTITY_H
