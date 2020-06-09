//
// Created by marcos on 6/8/20.
//

#include "NPC.h"
#include "../GameConstants.h"

NPC::NPC(SDL_Renderer &renderer, SDL_Rect &camera, float x, float y,
         std::string image) : Entity(camera, x, y), npcTexture(renderer, image) {}

void NPC::render() {
    Entity::updatePosition();
    Entity::render(npcTexture);
}



