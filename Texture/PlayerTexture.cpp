//
// Created by marcos on 6/6/20.
//

#include "PlayerTexture.h"

PlayerTexture::PlayerTexture(TextureRepository& repo, PlayerEquipment equipment)
                                : textureRepo(repo) {
    if (equipment.helmet != Nothing) helmet = &textureRepo.getTexture(equipment.helmet);
    else helmet = nullptr;
    head = &textureRepo.getTexture(equipment.head);
    body = &textureRepo.getTexture(equipment.body);
    if (equipment.shield != Nothing) shield = &textureRepo.getTexture(equipment.shield);
    else shield = nullptr;
    if (equipment.weapon != Nothing) weapon = &textureRepo.getTexture(equipment.weapon);
    else weapon = nullptr;
}

void PlayerTexture::renderFront(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 8, y - 15, 0);
    EntityTexture::render(body, x, y, frame);
    if (&textureRepo.getTexture(MagicHat) == helmet) { /*There was no other option*/
        EntityTexture::render(helmet, x + 7, y - 39, 0);
    } else {
        EntityTexture::render(helmet, x + 8, y - 15, 0);
    }
    EntityTexture::render(shield, x + 15, y, frame);
    EntityTexture::render(weapon, x, y - 10, frame);
}

void PlayerTexture::renderBack(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 8, y - 15, 3);
    EntityTexture::render(weapon, x + 5, y - 10, frame + 6);
    EntityTexture::render(shield, x, y - 15, frame + 6);
    EntityTexture::render(body, x, y, frame + 6);
    if (&textureRepo.getTexture(MagicHat) == helmet) { /*There was no other option*/
        EntityTexture::render(helmet, x + 8, y - 39, 3);
    } else {
        EntityTexture::render(helmet, x + 8, y - 19, 3);
    }
}

void PlayerTexture::renderRight(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 9, y - 15, 1);
    EntityTexture::render(shield, x + 3, y, frame + 18);
    EntityTexture::render(body, x, y, frame + 18);
    if (&textureRepo.getTexture(MagicHat) == helmet) { /*There was no other option*/
        EntityTexture::render(helmet, x + 8, y - 39, 1);
    } else {
        EntityTexture::render(helmet, x + 8, y - 19, 1);
    }
    EntityTexture::render(weapon, x, y - 10, frame + 18);
}

void PlayerTexture::renderLeft(int x, int y, int frame) {
    if (frame < 0 || frame > 5) throw SDLException("I dont have that character frame!");
    EntityTexture::render(head, x + 6, y - 15, 2);
    EntityTexture::render(weapon, x - 4, y - 10, frame + 12);
    EntityTexture::render(body, x, y, frame + 12);
    if (&textureRepo.getTexture(MagicHat) == helmet) { /*There was no other option*/
        EntityTexture::render(helmet, x + 6, y - 39, 2);
    } else {
        EntityTexture::render(helmet, x + 6, y - 19, 2);
    }
    EntityTexture::render(shield, x + 10, y, frame + 12);
}

