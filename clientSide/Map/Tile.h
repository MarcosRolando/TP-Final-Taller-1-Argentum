//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_TILE_H
#define ARGENTUM_TILE_H

#include "../Texture/TextureRepository.h"
#include "ItemDrop.h"
#include "Structure.h"
#include "../Character/Entity.h"
#include "Coordinate.h"
#include <memory>
#include "../../libs/GameEnums.h"
#include <list>
#include "../Spells/Spell.h"

class Tile {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture* tileTexture{nullptr};
    ItemDrop item;
    Structure structure;
    std::weak_ptr<Entity> entity;
    std::weak_ptr<Spell> spell;
    //The tile type
    int type;

public:
    //Initializes position and type
    explicit Tile(Coordinate position);

    void loadData(Texture& _tileTexture, Texture* sTexture = nullptr, int tileType = 0);

    void createItem(Texture& _itemTexture);

    void setStructure(Texture& sTexture);

    //Shows the tile
    void renderGround(SDL_Rect& camera);

    void renderStructure(SDL_Rect& camera);

    void renderEntity();

    void addEntity(std::shared_ptr<Entity>& _entity);

    void removeEntity();

    void addSpell(std::shared_ptr<Spell>& newSpell, SDL_Rect& camera);

    void destroyItem();
};


#endif //ARGENTUM_TILE_H
