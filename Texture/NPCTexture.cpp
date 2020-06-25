//
// Created by marcos on 6/8/20.
//

#include "NPCTexture.h"

NPCTexture::NPCTexture(TextureRepository& repo, TextureID texture) : textureRepo(repo) {
    body = &textureRepo.getTexture(texture);
}

void NPCTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame);
}

void NPCTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 6);
}

void NPCTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 18);
}

void NPCTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw TPException("I dont have that character frame!");
    EntityTexture::render(body, x + 4, y - 20, frame + 12);
}