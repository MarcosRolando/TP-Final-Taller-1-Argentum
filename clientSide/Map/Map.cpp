//
// Created by marcos on 6/7/20.
//

#include "Map.h"
#include <fstream>
#include <algorithm>
#include "../Client/GameConstants.h"
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

void Map::_addEntity(EntityData& data, std::shared_ptr<Entity>& entity) {
    if (data.currentDir != GameType::DIRECTION_STILL) {
        Coordinate destination = _calculateNewTile(data.pos,
                                                   data.currentDir);
        entity->move(data.currentDir, data.distanceMoved, false);
        entities.emplace(data.nickname, std::make_pair(std::move(entity),
                                                       data.pos));
        entitiesToUpdateTilePosition.emplace_back(&entities.at(data.nickname).first,
                                                  destination, data.nickname);
    } else {
        int tile = data.pos.i*TOTAL_HORIZONTAL_TILES + data.pos.j;
        tiles.at(tile).addEntity(entity);
        entities.emplace(data.nickname, std::make_pair(std::move(entity),
                                                       data.pos));
    }
}

void Map::addNPC(EntityData& data) {
    if (entities.count(data.nickname) == 0) {
        std::shared_ptr<Entity> npc = std::make_shared<NPC>(textureRepo,
                camera, data.pos.j*TILE_WIDTH,data.pos.i*TILE_HEIGHT, data.texture);
        _addEntity(data, npc);
    }
}

void Map::addPlayer(MapPlayerData& playerData) {
    if (entities.count(playerData.entityData.nickname) == 0) {
        std::shared_ptr<Entity> player = std::make_shared<Player>(textureRepo,camera,
                playerData.entityData.pos.j*TILE_WIDTH,playerData.entityData.pos.i*TILE_HEIGHT,
                playerData.equipment, playerData.isAlive);
        _addEntity(playerData.entityData, player);
    }
}

void Map::createItem(Coordinate position, TextureID itemTexture) {
    unsigned int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).createItem(textureRepo.getTexture(itemTexture));
}

void Map::moveEntity(std::string &nickname, GameType::Direction direction,
                     unsigned int distanceTravelled, bool reachedDestination) {

    if (entities.count(nickname) == 1) { /*Si no lo mataron en el update*/
        Entity* entity = entities.at(nickname).first.get();
        GameType::Direction previousDirection = entity->move(direction,
                                        distanceTravelled, reachedDestination);
        if (previousDirection == GameType::DIRECTION_STILL) { /*Se empezo a mover de tile*/
            Coordinate oldPosition = entities.at(nickname).second;
            verifyQueueSound(oldPosition, Step, 3);
            Coordinate newPosition = _calculateNewTile(oldPosition, direction);
            int tile = oldPosition.i*TOTAL_HORIZONTAL_TILES + oldPosition.j;
            tiles.at(tile).removeEntity();
            entitiesToUpdateTilePosition.emplace_back(&entities.at(nickname).first,
                                                    newPosition, std::move(nickname));
        }
    }
}

void Map::verifyQueueSound(Coordinate tile, SoundID sound, int maxDistance) {
    Coordinate playerPos = entities.at(playerNickname).second;
    int distance = std::abs(playerPos.j - tile.j) + std::abs(playerPos.i - tile.i);
    if (distance <= maxDistance) {
        soundPlayer.queueSound(sound);
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
                entities.at(std::get<2>(entity)).second = std::get<1>(entity);
                tiles.at(tile).addEntity(*std::get<0>(entity));
            }
        }
        entitiesToUpdateTilePosition.clear();
    }
}

void Map::setCameraOn(std::string& nickname) {
    entities.at(nickname).first->activateCamera();
}

void Map::removeEntity(std::string &nickname) {
    Coordinate position = entities.at(nickname).second;
    int tile = position.i * TOTAL_HORIZONTAL_TILES + position.j;
    tiles.at(tile).removeEntity();
    entities.erase(nickname);
}

void Map::equipOnPlayer(std::string &nickname, GameType::EquipmentPlace place,
                        TextureID equipment) {
    Entity* entity = entities.at(nickname).first.get();
    auto player = dynamic_cast<Player*>(entity);
    if (player) {
        player->equip(place, equipment);
    }
}

void Map::killPlayer(std::string &nickname) {
    Entity* entity = entities.at(nickname).first.get();
    Coordinate position = entities.at(nickname).second;
    verifyQueueSound(position, Death, 10);
    auto player = dynamic_cast<Player*>(entity);
    if (player) {
        player->kill();
    }
}

void Map::revivePlayer(std::string &nickname) {
    Entity* entity = entities.at(nickname).first.get();
    auto player = dynamic_cast<Player*>(entity);
    if (player) {
        player->revive();
    }
}

void Map::addSpell(Coordinate position, TextureID spellTexture) {
    int tile = position.i*TOTAL_HORIZONTAL_TILES + position.j;
    std::shared_ptr<Spell> spell(new Spell(textureRepo.getTexture(spellTexture),
            camera,position.j*TILE_WIDTH, position.i*TILE_HEIGHT)); //No uso make shared ya que el spell
                                                                            //no lo borro del weak ptr al destruirse
                                                                            // y con make shared eso resultaria en conservar mas memoria
    tiles.at(tile).addSpell(spell, camera);
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
    Entity* entity = entities.at(nickname).first.get();
    Coordinate oldPosition = entities.at(nickname).second;
    int oldTile = oldPosition.i*TOTAL_HORIZONTAL_TILES + oldPosition.j;
    tiles.at(oldTile).removeEntity();
    int newTile = newPosition.i*TOTAL_HORIZONTAL_TILES + newPosition.j;
    entity->setPosition(newPosition.j*TILE_WIDTH, newPosition.i*TILE_HEIGHT);
    if (isMyPlayer) {
        entity->activateCamera();
    }
    tiles.at(newTile).addEntity(entities.at(nickname).first);
    entities.at(nickname).second = newPosition;
}

void Map::setPlayerNickname(const std::string &nickname) {
    playerNickname = nickname;
}

void Map::changeEntityLookDirection(std::string& nickname, GameType::Direction direction) {
    Entity* entity = entities.at(nickname).first.get();
    entity->setLookDirection(direction);
}
