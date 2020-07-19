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
#include "../Miscellaneous/Spell.h"

class Tile {
private:
    SDL_Rect box{};
    Texture* tileTexture{nullptr};
    ItemDrop item;
    Structure structure;
    std::weak_ptr<Entity> entity;
    std::weak_ptr<Spell> spell;
    int type; //La mayoria de las texturas de los tiles son varias en una
              //con esto puedo especificar cual quiero en particular

public:
    explicit Tile(Coordinate position);

    /*Carga la data inicial del tile, esto es, el tipo de piso y si guarda una estructura*/
    void loadData(Texture& _tileTexture, Texture* sTexture = nullptr, int tileType = 0);

    /*Crea un item en el tile*/
    void createItem(Texture& _itemTexture);

    /*Renderiza el piso del tile*/
    void renderGround(SDL_Rect& camera);

    /*Renderiza la estructura (si tuviera)*/
    void renderStructure(SDL_Rect& camera);

    /*Renderiza la entity (si tuviera)*/
    void renderEntity();

    /*Agrega un entity al tile*/
    void addEntity(std::shared_ptr<Entity>& _entity);

    /*Elimina el entity del tile*/
    void removeEntity();

    /*Agrega un spell al tile*/
    void addSpell(std::shared_ptr<Spell>& newSpell, SDL_Rect& camera);

    /*Elimina el spell del tile*/
    void destroyItem();
};


#endif //ARGENTUM_TILE_H
