//
// Created by marcos on 6/8/20.
//

#include "NPCTexture.h"
#include "../Client/GameConstants.h"

NPCTexture::NPCTexture(TextureRepository& repo, TextureID texture, std::string&& _level,
                        const std::string& _nickname) : textureRepo(repo),
                    textFont("/var/Argentum/Assets/Fonts/Raleway-Medium.ttf", 20),
                    nickname(textFont, repo.getRenderer(), _nickname),
                    level(textFont, repo.getRenderer(), std::move(_level)) {

    levelOffset = nickname.getTextTextureWidth();
    if (levelOffset == 0) {
        levelOffset = TILE_WIDTH/2 - 30;
    }
    body = &textureRepo.getTexture(texture);
}

void NPCTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame);
    nickname.render(x + 20, y + TILE_HEIGHT - 15);
    level.render(x + 20 + levelOffset, y + TILE_HEIGHT - 15);
}

void NPCTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 6);
    nickname.render(x + 20, y + TILE_HEIGHT - 15);
    level.render(x + 20 + levelOffset, y + TILE_HEIGHT - 15);
}

void NPCTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 18);
    nickname.render(x + 20, y + TILE_HEIGHT - 15);
    level.render(x + 20 + levelOffset, y + TILE_HEIGHT - 15);
}

void NPCTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 12);
    nickname.render(x + 20, y + TILE_HEIGHT - 15);
    level.render(x + 20 + levelOffset, y + TILE_HEIGHT - 15);
}

void NPCTexture::setLevel(const std::string &_level) {
    *(level.updateText(_level));
}

