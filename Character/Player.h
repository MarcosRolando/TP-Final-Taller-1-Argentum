//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "Entity.h"
#include "../Texture/PlayerTexture.h"

class Player : public Entity {
private:
    PlayerTexture pTexture;

public:
    Player(TextureRepository& repo, SDL_Rect& camera, float x, float y,
                                                    PlayerEquipment& images);
    void render() override;
};


#endif //ARGENTUM_PLAYER_H
