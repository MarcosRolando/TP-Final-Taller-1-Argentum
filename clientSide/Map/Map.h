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
#include "../Miscellaneous/Spell.h"
#include "../Client/CitizenData.h"
#include "../Sound/SoundPlayer.h"
#include "../Miscellaneous/Arrow.h"

class Map {
private:
    TextureRepository& textureRepo;
    SoundPlayer& soundPlayer;
    std::vector<Tile> tiles;
    SDL_Rect& camera;
    std::unordered_map<std::string, std::pair<std::shared_ptr<Entity>, Coordinate>> entities;
    std::list<std::tuple<std::shared_ptr<Entity>*, Coordinate, std::string>> entitiesToUpdateTilePosition; /*Esto es para no pisar entities entre si cuando terminan de moverse*/
    std::list<std::shared_ptr<Spell>> spells;
    std::list<std::unique_ptr<Arrow>> arrows;
    std::string playerNickname;

public:
    Map(TextureRepository& repo, SDL_Rect& camera, SoundPlayer& soundPlayer);



    void setSize(int rows, int columns);

    void loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                      CitizenData& citizen);

    void createItem(Coordinate position, TextureID itemTexture);

    void addNPC(EntityData& data);

    void addPlayer(MapPlayerData& playerData);

    /*Desplaza a la entidad en la direccion recibida y comienza su interpolacion interna para que se vea fluido*/
    void moveEntity(std::string& nickname, GameType::Direction direction,
            unsigned int distanceTravelled, bool reachedDestination);

    void setCameraOn(std::string& nickname);

    void removeEntity(std::string& nickname);

    void equipOnPlayer(std::string& nickname, GameType::EquipmentPlace place,
                        TextureID equipment);

    void killPlayer(std::string& nickname);

    void revivePlayer(std::string &nickname);

    void addSpell(Coordinate position, TextureID spellTexture);

    void addArrow(std::string& archerNickname, Coordinate target, TextureID arrowTexture);

    void update(double timeStep = 0);

    void destroyItem(Coordinate itemPosition);

    void teleportEntity(const std::string& nickname, Coordinate newPosition,
                        bool isMyPlayer);

    void setPlayerNickname(const std::string& nickname);

    void verifyQueueSound(Coordinate tile, SoundID sound, int maxDistance);

    void changeEntityLookDirection(std::string& nickname, GameType::Direction direction);

    void render();

private:
    static Coordinate _calculateNewTile(Coordinate position, GameType::Direction direction);
    void _updateSpells(double timeStep);
    void _updateArrows(double timeStep);
    void _moveEntitiesToNewTile();
    void _addEntity(EntityData& data, std::shared_ptr<Entity>& entity);
    void _renderGround();
    void _renderStructures();
    void _renderNPCS();
    void _renderArrows();
};


#endif //ARGENTUM_MAP_H
