//
// Created by marcos on 6/9/20.
//

#ifndef ARGENTUM_ENTITY_H
#define ARGENTUM_ENTITY_H

#include "../Texture/EntityTexture.h"
#include "../Shared/GameEnums.h"
#include <list>
#include <memory>
#include "../Spells/Spell.h"

/*Clase Abstracta*/

class Entity {
private:
    SDL_Rect& camera;
    int currentFrame;
    GameType::Direction moveDirection, lastDirection;
    float xPosition, width;
    float yPosition, height;
    float totalDistanceMoved{0};

protected:
    bool cameraFollows{false};
    std::weak_ptr<Spell> spell;

public:
    Entity(SDL_Rect& camera, float x, float y);
    GameType::Direction move(GameType::Direction direction, unsigned int distanceTravelled, bool reachedDestination);
    void render(EntityTexture& eTexture);
    virtual void render() = 0;
    void updateCamera();
    void activateCamera();
    void addSpell(std::shared_ptr<Spell>& _spell);
    std::weak_ptr<Spell>& getSpell();
    void setPosition(float _xPosition, float _yPosition);

private:
    static bool _checkCollision(SDL_Rect a, SDL_Rect b);
    void _renderLastDirection(EntityTexture& eTexture);
    void _modifyPosition(GameType::Direction direction, float distance);
    void _updateFrame(bool reachedDestination);
};


#endif //ARGENTUM_ENTITY_H
