//
// Created by marcos on 6/8/20.
//

#include "NPC.h"
#include "GameConstants.h"

NPC::NPC(SDL_Renderer &renderer, SDL_Rect &camera, float x, float y,
         std::string image) : npcTexture(renderer, image), camera(camera) {

        movedOffset = 0;
        currentFrame = 0;
        moveDirection = STILL;
        xPosition = x;
        yPosition = y;
}

void NPC::_updatePosition() {
    //Calculate time step
    float timeStep = moveTime.getTicks() / 1000.f;
    float offset = SPEED*timeStep;
    if (moveDirection != STILL) {
        if ( (movedOffset + offset) >= TILE_WIDTH*2/*tileScale*/) {
            offset = TILE_WIDTH*2 - movedOffset;
        }
        movedOffset += offset;
        switch (moveDirection) {
            case UP:
                yPosition -= offset;
                break;
            case DOWN:
                yPosition += offset;
                break;
            case RIGHT:
                xPosition += offset;
                break;
            case LEFT:
                xPosition -= offset;
                break;
            case STILL:
                //do nothing
                break;
        }
    }
    if (moveDirection != STILL) {
        for (int i = 0; i < 6; ++i) { /*6 es la cantidad de frames distintos del body*/
            if (movedOffset < ((float)TILE_WIDTH*2/6 * (float)(i+1))) {
                currentFrame = i;
                break;
            }
            if (i == 5) {
                currentFrame = 0;
                moveDirection = STILL;
                movedOffset = 0;
            }
        }
    }
}

void NPC::render() {
    _updatePosition();
    moveTime.start(); //reseteo
    switch (moveDirection) {
        case UP:
            npcTexture.renderBack((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, currentFrame);
            break;
        case DOWN:
            npcTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, currentFrame);
            break;
        case RIGHT:
            npcTexture.renderRight((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, currentFrame);
            break;
        case LEFT:
            npcTexture.renderLeft((int)(xPosition) - camera.x,
                                (int)(yPosition) - camera.y, currentFrame);
            break;
        case STILL:
            npcTexture.renderFront((int)(xPosition) - camera.x,
                                 (int)(yPosition) - camera.y, 0);
            break;
    }
}

void NPC::move(Direction direction) {
    if (moveDirection == STILL) moveDirection = direction;
}


