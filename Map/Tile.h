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
#include "../Shared/GameEnums.h"
#include <list>

class Tile {
private:
    //The attributes of the tile
    SDL_Rect box{};
    Texture* tileTexture{nullptr};
    ItemDrop item;
    Structure structure;
    std::unique_ptr<Entity> entity{nullptr};
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

    void addItemDrop(Texture& itemTexture);

    void addEntity(std::unique_ptr<Entity> _entity);

    void moveEntity(GameType::Direction direction, unsigned int distanceTravelled,
                    std::list<Entity*>& movingEntities);

    void setCameraOn();

    void removeEntity();

    std::unique_ptr<Entity> getEntity();

    void equipOnPlayer(GameType::EquipmentPlace place, TextureID equipment);

    void killPlayer();
};


#endif //ARGENTUM_TILE_H
