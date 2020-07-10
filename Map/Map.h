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
#include "../Spells/Spell.h"
#include "../Client/CitizenData.h"

class Map {
private:
    TextureRepository& textureRepo;
    std::vector<Tile> tiles;
    SDL_Rect& camera;
    std::unordered_map<std::string, Coordinate> entities;
    std::list<std::tuple<std::unique_ptr<Entity>, Coordinate, std::string>> entitiesToUpdateTilePosition; /*Esto es para no pisar entities entre si cuando terminan de moverse*/
    std::list<std::shared_ptr<Spell>> spells; /*Comparto ownership cosa que si el entity muere no pierdo la animacion del hechizo*/

public:
    Map(TextureRepository& repo, SDL_Rect& camera);

    void renderGround();

    void renderStructures();

    void renderNPCS();

    void setSize(int rows, int columns);

    void loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                      CitizenData& citizen);

    void createItem(Coordinate position, TextureID itemTexture);

    void addNPC(EntityData& data);

    void addPlayer(MapPlayerData& playerData);

    /*Desplaza a la entidad en la direccion recibida y comienza su interpolacion interna para que se vea fluido*/
    void moveEntity(std::string& nickname, GameType::Direction direction,
            unsigned int distanceTravelled, bool reachedDestination);

    void setCameraOn(Coordinate position);

    void removeEntity(std::string& nickname);

    void equipOnPlayer(std::string& nickname, GameType::EquipmentPlace place,
                        TextureID equipment);

    void killPlayer(std::string& nickname);

    void revivePlayer(std::string &nickname);

    void addSpell(Coordinate position, TextureID spellTexture);

    void update(float timeStep = 0);

    void destroyItem(Coordinate itemPosition);

    void teleportEntity(const std::string& nickname, Coordinate newPosition,
                        bool isMyPlayer);

private:
    static Coordinate _calculateNewTile(Coordinate position, GameType::Direction direction);
    void _updateSpellsFrame(float timeStep);
    void _moveEntitiesToNewTile();
};


#endif //ARGENTUM_MAP_H
