//
// Created by marcos on 6/8/20.
//

#include "NPCTexture.h"
#include "../Client/GameConstants.h"

NPCTexture::NPCTexture(TextureRepository& repo, TextureID texture, std::string&& _level) : textureRepo(repo),
                    textFont("/var/Argentum/Assets/Fonts/Raleway-Medium.ttf", 20),
                    level(textFont, repo.getRenderer(), std::move(_level)) {
    body = &textureRepo.getTexture(texture);
}

void NPCTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void NPCTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 6);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void NPCTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 18);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void NPCTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 12);
    level.render(x + TILE_WIDTH/2 - 10, y + TILE_HEIGHT - 20);
}

void NPCTexture::setLevel(std::string &_level) {
    *(level.updateText(_level));
}

