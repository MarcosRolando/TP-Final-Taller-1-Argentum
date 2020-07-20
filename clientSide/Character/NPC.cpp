//
// Created by marcos on 6/8/20.
//

#include "NPC.h"

NPC::NPC(TextureRepository& repo, SDL_Rect &camera, float x, float y,
         TextureID texture, std::string&& level) : Entity(camera, x, y),
         npcTexture(repo, texture, std::move(level)) {}

void NPC::render() {
    Entity::render(npcTexture);
}

void NPC::updateLevel(int level) {
    npcTexture.setLevel(std::to_string(level));
}
