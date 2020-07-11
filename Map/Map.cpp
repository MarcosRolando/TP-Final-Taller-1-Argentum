//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include <algorithm>
#include "../GameConstants.h"
#include "../Character/NPC.h"
#include "../Character/Player.h"

Map::Map(TextureRepository& repo, SDL_Rect& camera, SoundPlayer& soundPlayer) :
                    textureRepo(repo), soundPlayer(soundPlayer),camera(camera){
    this->camera = camera;
}

void Map::renderGround() {
    for (int i = 0; i < (VISIBLE_VERTICAL_TILES + 1); ++i) {
        for (int j = 0; j < (VISIBLE_HORIZONTAL_TILES + 1); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderGround(camera);
        }
    }
}

void Map::renderStructures() {
    for (int i = -1; i < (VISIBLE_VERTICAL_TILES + 3); ++i) {
        for (int j = -1; j < (VISIBLE_HORIZONTAL_TILES + 3); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderStructure(camera);
        }
    }
}

void Map::renderNPCS() {
    for (int i = -2; i < (VISIBLE_VERTICAL_TILES + 2); ++i) {
        for (int j = -2; j < (VISIBLE_HORIZONTAL_TILES + 2); ++j) {
            float x = (float)camera.x + (float)j * TILE_WIDTH;
            float y = (float)camera.y + (float)i * TILE_HEIGHT;
            if (x >= LEVEL_WIDTH || x < 0) continue;
            if (y >= LEVEL_HEIGHT || y < 0) continue;
            int xTile = floor(x / TILE_WIDTH);
            int yTile = floor(y / TILE_HEIGHT);
            int tile = yTile*TOTAL_HORIZONTAL_TILES + xTile;
            tiles.at(tile).renderEntity();
        }
    }
}

void Map::setSize(int rows, int columns) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            tiles.emplace_back(Coordinate{i, j});
        }
    }
}

void Map::loadTileData(Coordinate position, FloorTypeTexture floor, TextureID structure,
                       CitizenData& citizen) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    if (structure != Nothing) {
        tiles.at(tile).loadData(textureRepo.getTexture(floor.texture),
                &textureRepo.getTexture(structure), floor.index);
    } else {
        tiles.at(tile).loadData(textureRepo.getTexture(floor.texture),
                nullptr, floor.index);
    }
    if (citizen.texture != Nothing) {
        EntityData data = {citizen.texture, std::move(citizen.nickname), position,
                           GameType::DIRECTION_STILL, 0};
        addNPC(data);
    }
}

void Map::addNPC(EntityData& data) {
    if (entities.count(data.nickname) == 0) {
        if (data.currentDir != GameType::DIRECTION_STILL) {
            Coordinate destination = _calculateNewTile(data.pos,
                                                       data.currentDir);
            std::unique_ptr<NPC> npc(new NPC(textureRepo,
                    camera, data.pos.j*TILE_WIDTH,data.pos.i*TILE_HEIGHT, data.texture));
            npc->move(data.currentDir, data.distanceMoved, false);
            entitiesToUpdateTilePosition.emplace_back(std::move(npc), destination,
                                                      data.nickname);
        } else {
            int tile = data.pos.i*TOTAL_HORIZONTAL_TILES + data.pos.j;
            tiles.at(tile).addEntity(std::unique_ptr<Entity>(new NPC(textureRepo,
                    camera, data.pos.j*TILE_WIDTH,data.pos.i*TILE_HEIGHT, data.texture)));
        }
        entities.emplace(std::move(data.nickname), data.pos); //todo recibir el nickname de los citizens sino no los cargo
    }
}

void Map::addPlayer(MapPlayerData& playerData) {
    if (entities.count(playerData.entityData.nickname) == 0) {
        if (playerData.entityData.currentDir != GameType::DIRECTION_STILL) {
            Coordinate destination = _calculateNewTile(playerData.entityData.pos,
                                     playerData.entityData.currentDir);
            std::unique_ptr<Player> player(new Player(textureRepo,camera,
                    playerData.entityData.pos.j*TILE_WIDTH,playerData.entityData.pos.i*TILE_HEIGHT,
                    playerData.equipment, playerData.isAlive));
            player->move(playerData.entityData.currentDir, playerData.entityData.distanceMoved, false);
            entitiesToUpdateTilePosition.emplace_back(std::move(player), destination,
                                                      playerData.entityData.nickname);
        } else {
            int tile = playerData.entityData.pos.i*TOTAL_HORIZONTAL_TILES + playerData.entityData.pos.j;
            tiles.at(tile).addEntity(std::unique_ptr<Entity>(new Player(textureRepo,camera,
                    playerData.entityData.pos.j*TILE_WIDTH,playerData.entityData.pos.i*TILE_HEIGHT,
                    playerData.equipment, playerData.isAlive)));
        }
        entities.emplace(std::move(playerData.entityData.nickname), playerData.entityData.pos);
    }
}

void Map::createItem(Coordinate position, TextureID itemTexture) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).createItem(textureRepo.getTexture(itemTexture));
}

void Map::moveEntity(std::string &nickname, GameType::Direction direction,
                     unsigned int distanceTravelled, bool reachedDestination) {

    if (entities.count(nickname) == 1) { /*Si no lo mataron en el update*/
        Coordinate entityPosition = entities.at(nickname);
        int tile = entityPosition.i * TOTAL_HORIZONTAL_TILES + entityPosition.j;
        GameType::Direction previousDirection = tiles.at(tile).moveEntity(direction,
                                            distanceTravelled, reachedDestination);
        if (previousDirection == GameType::DIRECTION_STILL) { /*Se empezo a mover de tile*/
            std::unique_ptr<Entity> entity = tiles.at(tile).getEntity();
            entityPosition = _calculateNewTile(entityPosition, direction);
            entitiesToUpdateTilePosition.emplace_back(std::move(entity), entityPosition,
                                                std::move(nickname));
        }
    }
}

Coordinate Map::_calculateNewTile(Coordinate position, GameType::Direction direction) {
    switch (direction) {
        case GameType::DIRECTION_UP:
            position.i -= 1;
            break;
        case GameType::DIRECTION_DOWN:
            position.i += 1;
            break;
        case GameType::DIRECTION_LEFT:
            position.j -= 1;
            break;
        case GameType::DIRECTION_RIGHT:
            position.j += 1;
            break;
        case GameType::DIRECTION_STILL:
            //do nothing
            break;
    }
    return position;
}

void Map::_moveEntitiesToNewTile() {
    if (!entitiesToUpdateTilePosition.empty()) {
        for (auto && entity : entitiesToUpdateTilePosition) {
            if (entities.count(std::get<2>(entity)) == 1) { //esto es para el sneaky motherfucker caso donde lo mueven al nuevo tile y matan en el mismo update
                int tile = std::get<1>(entity).i * TOTAL_HORIZONTAL_TILES + std::get<1>(entity).j;
                entities.at(std::get<2>(entity)) = std::get<1>(entity);
                tiles.at(tile).addEntity(std::move(std::get<0>(entity)));
            }
        }
        entitiesToUpdateTilePosition.clear();
    }
}

void Map::setCameraOn(Coordinate position) {
    int tile = position.i * TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).setCameraOn();
}

void Map::removeEntity(std::string &nickname) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).removeEntity();
    entities.erase(nickname);
}

void Map::equipOnPlayer(std::string &nickname, GameType::EquipmentPlace place,
                        TextureID equipment) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).equipOnPlayer(place, equipment);
}

void Map::killPlayer(std::string &nickname) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).killPlayer();
}

void Map::revivePlayer(std::string &nickname) {
    Coordinate position = entities.at(nickname);
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).revivePlayer();
}

void Map::addSpell(Coordinate position, TextureID spellTexture) {
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    std::shared_ptr<Spell> spell(new Spell(textureRepo.getTexture(spellTexture),
            camera,position.j*TILE_WIDTH, position.i*TILE_HEIGHT));
    tiles.at(tile).addSpell(spell, camera,
                            position.j*TILE_WIDTH, position.i*TILE_HEIGHT);
    spells.emplace_back(std::move(spell));
}

void Map::update(float timeStep) {
    _moveEntitiesToNewTile();
    _updateSpellsFrame(timeStep);
}

static bool shouldSpellBeRemoved(std::shared_ptr<Spell>& spell) {
    if (spell) {
        return spell->finishedAnimation();
    }
    return true;
}

void Map::_updateSpellsFrame(float timeStep) {
    if (!spells.empty()) {
        for (auto & spell : spells) {
            if (spell) {
                spell->updateFrame(timeStep);
            }
        }
        spells.erase(std::remove_if(spells.begin(), spells.end(),
                                    shouldSpellBeRemoved), spells.end());
    }
}

void Map::destroyItem(Coordinate itemPosition) {
    int tile = itemPosition.i*TOTAL_HORIZONTAL_TILES + itemPosition.j;
    tiles.at(tile).destroyItem();
}

void Map::teleportEntity(const std::string &nickname, Coordinate newPosition,
                         bool isMyPlayer) {
    Coordinate oldPosition = entities.at(nickname);
    int oldTile = oldPosition.i*TOTAL_HORIZONTAL_TILES + oldPosition.j;
    std::unique_ptr<Entity> entity = tiles.at(oldTile).getEntity();
    int newTile = newPosition.i*TOTAL_HORIZONTAL_TILES + newPosition.j;
    entity->setPosition(newPosition.j*TILE_WIDTH, newPosition.i*TILE_HEIGHT);
    if (isMyPlayer) {
        entity->activateCamera();
    }
    tiles.at(newTile).addEntity(std::move(entity));
    entities.at(nickname) = newPosition;
}
