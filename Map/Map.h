//
// Created by marcos on 6/7/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

/*Guarda las texturas de los tiles (asi no guardo mas de una vez las texturas de
 * un tile) y guarda tiles*/

#include "Tile.h"
#include <vector>
#include "../Texture/TextureRepository.h"
#include "Structure.h"
#include "../Client/ProtocolEnumTranslator.h"
#include "../Texture/PlayerEquipment.h"
#include <list>
#include "../Client/EntityData.h"

class Map {
private:
    TextureRepository& textureRepo;
    std::vector<Tile> tiles;
    SDL_Rect& camera;
    std::unordered_map<std::string, Coordinate> entities;
    std::list<Entity*> movingEntities; /*Las entitites que debo interpolar*/
    std::list<std::tuple<std::unique_ptr<Entity>, Coordinate>> entitiesToUpdateTilePosition; /*Esto es para no pisar entities entre si cuando terminan de moverse*/

public:
    Map(TextureRepository& repo, SDL_Rect& camera);

    void renderGround();

    void renderStructures();

    void renderNPCS();

    void setSize(int rows, int columns);

    void loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                      TextureID entity);

    void createItem(Coordinate position, TextureID itemTexture);

    void addNPC(EntityData& data);

    void addPlayer(MapPlayerData& playerData);

    /*Desplaza a la entidad en la direccion recibida y comienza su interpolacion interna para que se vea fluido*/
    void moveEntity(std::string& nickname, GameType::Direction direction,
            unsigned int distanceTravelled, bool reachedDestination);

    void updateInterpolation(float timeStep);

    void setCameraOn(Coordinate position);

    void removeEntity(std::string& nickname);

    void equipOnPlayer(std::string& nickname, GameType::EquipmentPlace place,
                        TextureID equipment);

    void killPlayer(std::string& nickname);

private:
    static Coordinate _calculateNewTile(Coordinate position, GameType::Direction direction);
    void _moveEntitiesToNewTile();
};


#endif //ARGENTUM_MAP_H
