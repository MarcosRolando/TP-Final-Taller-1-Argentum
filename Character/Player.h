//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include "Entity.h"
#include "../Texture/PlayerTexture.h"
#include "../Texture/NPCTexture.h"

class Player : public Entity {
private:
    PlayerTexture pTexture;
    NPCTexture ghostTexture;
    bool isDead{false};

public:
    Player(TextureRepository& repo, SDL_Rect& camera, float x, float y,
                                                    PlayerEquipment& images);
    void render(float timeStep) override;
};


#endif //ARGENTUM_PLAYER_H