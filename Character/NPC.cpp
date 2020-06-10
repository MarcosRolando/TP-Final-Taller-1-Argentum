//
// Created by marcos on 6/8/20.
//

#include "NPC.h"
#include "../GameConstants.h"

NPC::NPC(TextureRepository& repo, SDL_Rect &camera, float x, float y,
         TextureID texture) : Entity(camera, x, y), npcTexture(repo, texture) {}

void NPC::render() {
    Entity::updatePosition();
    Entity::render(npcTexture);
}



