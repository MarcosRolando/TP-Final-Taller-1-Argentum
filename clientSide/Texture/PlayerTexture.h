//
// Created by marcos on 6/6/20.
//

#ifndef ARGENTUM_PLAYERTEXTURE_H
#define ARGENTUM_PLAYERTEXTURE_H


#include "EntityTexture.h"
#include "../../libs/TPException.h"
#include "TextureRepository.h"
#include "PlayerEquipment.h"
#include "../../libs/GameEnums.h"

/*Representa la textura de un player*/

class PlayerTexture : public EntityTexture {
private:
    TextureRepository& textureRepo;
    Texture* helmet;
    Texture* head;
    Texture* body;
    Texture* shield;
    Texture* weapon;
    Font textFont;
    Text nickname, level;
    int levelOffset{0};

public:
    PlayerTexture(TextureRepository& repo, PlayerEquipment equipment, std::string&& _level,
                    const std::string& _nickname = "");

    void renderFront(int x, int y, int frame) override;
    void renderBack(int x, int y, int frame) override;
    void renderRight(int x, int y, int frame) override;
    void renderLeft(int x, int y, int frame) override;

    void setLevel(const std::string &_level);

    /*Cambia una textura del player*/
    void equip(GameType::EquipmentPlace place, TextureID equipment);
};


#endif //ARGENTUM_PLAYERTEXTURE_H
