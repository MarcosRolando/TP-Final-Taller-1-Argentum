//
// Created by agustin on 7/6/20.
//

#include <queue>
#include <unordered_map>
#include <memory>
#include "Map.h"
#include "../Entities/AttackResult.h"
#include "../Config/Calculator.h"
#include "../Entities/Citizens/CitizenFactory.h"
#include "../Config/MapFileReader.h"
#include <msgpack.hpp>


#define RESPAWN_RANGE 3

//////////////////////////////PRIVATE/////////////////////////////

//Retorna la distancia (siempre positiva) entre las dos coordenadas
unsigned int Map::_getDistance(Coordinate a, Coordinate b) {
    return std::abs((a.iPosition - b.iPosition) + (a.jPosition - b.jPosition));
}


//Indica si la coordenada esta en el rango de posiciones del mapa
bool Map::_isCoordinateValid(Coordinate coordinate) const {
    return (coordinate.jPosition >= 0) && (coordinate.jPosition < (int)tiles[0].size())
           && (coordinate.iPosition >= 0) && (coordinate.iPosition < (int)tiles.size());
}


bool Map::_areCoordinatesEqual(Coordinate a, Coordinate b){
    return (a.iPosition == b.iPosition) && (a.jPosition == b.jPosition);
}

void Map::_buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topLeft, Coordinate& bottomRight) const {
    Coordinate aux{};
    aux.iPosition = static_cast<int>(center.iPosition - range);
    aux.jPosition = static_cast<int>(center.jPosition - range);
    topLeft = _getValidCoordinate(aux);
    aux.iPosition = static_cast<int>(center.iPosition + range);
    aux.jPosition = static_cast<int>(center.jPosition + range);
    bottomRight = _getValidCoordinate(aux);
}

Coordinate Map::_getValidCoordinate(Coordinate coordinate) const {
    if (coordinate.jPosition >= (int)tiles[0].size()) {
        coordinate.jPosition = (int)tiles[0].size() - 1;
    } else if (coordinate.jPosition < 0) {
        coordinate.jPosition = 0;
    }
    if (coordinate.iPosition >= (int)tiles.size()) {
        coordinate.iPosition = (int)tiles.size() - 1;
    } else if (coordinate.iPosition < 0) {
        coordinate.iPosition = 0;
    }
    return coordinate;
}


//Guarda en nodes y parentsAndChilds los nodos correspondientes, revisando los
//nodos que se encuentren adyacentes a referencia, tambien actualiza las distancias
//de los nodos de ser necesario
void Map::_storeAdjacentPositions(
        PointAndDistance refference, std::unordered_map<Coordinate, unsigned int>& distances,
        std::unordered_map<Coordinate, Coordinate>& parentsAndChilds,
        std::priority_queue<PointAndDistance, std::vector<PointAndDistance>,
                            InverseCoordinateDistance>& nodes,
        Coordinate destination) const {
    Coordinate topLeft{}, bottomRight{};
    PointAndDistance aux{};
    _buildSearchRegion(refference.point, 1, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i <= bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j <= bottomRight.jPosition; ++j) {
            aux.point.iPosition = i;
            aux.point.jPosition = j;
            aux.distance = _getDistance(refference.point, aux.point);
            //if (esta a distancia 1 y (la posicion es alcanzable o tiene un jugador) y no esta en una ciudad)
            if (((aux.distance == 1) && (tiles[i][j].isAvailable() ||
                tiles[i][j].hasMonsterTarget())) && !tiles[i][j].isInCity()) {
                aux.distance += refference.distance + _getDistance(aux.point, destination);
                if ((distances.count(aux.point) == 0) ||
                    (distances.at(aux.point) > aux.distance)) {
                    nodes.push(aux);
                    distances[aux.point] = aux.distance;
                    parentsAndChilds[aux.point] = refference.point;
                }
            }
        }
    }
}

void Map::_storePath(Coordinate initialPosition, Coordinate desiredPosition,
                     const std::unordered_map<Coordinate, Coordinate>& parentsAndChilds,
                     std::list<Coordinate>& path) {
    Coordinate aux = desiredPosition;
    while (!_areCoordinatesEqual(aux, initialPosition)) {
        path.push_front(aux);
        aux = parentsAndChilds.at(aux);
    }
}


bool Map::_isReachable(Coordinate position) const {
    Coordinate topLeft{};
    Coordinate bottomRight{};
    Coordinate aux{};
    _buildSearchRegion(position, 1, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i <= bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j <= bottomRight.jPosition; ++j) {
            aux = {i, j};
            if ((_getDistance(position, aux) == 1) && (tiles[i][j].isAvailable() && !tiles[i][j].isInCity())) {
                return true;
            }
        }
    }
    return false;
}



void Map::_initializeConstructorMaps(
        std::unordered_map<std::string, GameType::Entity> &entities,
        std::unordered_map<std::string, GameType::Structure> &structures,
        std::unordered_map<std::string, GameType::FloorType> &floors) {
    entities ={{"Nothing", GameType::Entity::GUARD}, {"Priest", GameType::Entity::PRIEST},
             {"Trader", GameType::Entity::TRADER}, {"Banker", GameType::Entity::BANKER}};
    structures = {{"BoneGuy", GameType::Structure::BONE_GUY}, {"BrokenRipStone", GameType::Structure::BROKEN_RIP_STONE},
            {"Bush", GameType::Structure::BUSH}, {"DeadBush", GameType::Structure::DEAD_BUSH},
            {"DeadGuy", GameType::Structure::DEAD_GUY}, {"DeadTree", GameType::Structure::DEAD_TREE},
            {"FatTree", GameType::Structure::FAT_TREE}, {"HangedGuy", GameType::Structure::HANGED_GUY},
            {"House1", GameType::Structure::HOUSE1}, {"House2", GameType::Structure::HOUSE2},
            {"House3", GameType::Structure::HOUSE3}, {"LongTree", GameType::Structure::LONG_TREE},
            {"PalmTree", GameType::Structure::PALM_TREE}, {"RipStone", GameType::Structure::RIP_STONE},
            {"Tree", GameType::Structure::TREE}, {"VeryDeadGuy", GameType::Structure::VERY_DEAD_GUY},
            {"SunkenColumn", GameType::Structure::SUNKEN_COLUMN}, {"SunkenShip", GameType::Structure::SUNKEN_SHIP},
            {"Nothing", GameType::Structure::NO_STRUCTURE}};

    floors = {{"Grass0", GameType::FloorType::GRASS0}, {"Grass1", GameType::FloorType::GRASS1},
            {"Grass2", GameType::FloorType::GRASS2}, {"Grass3", GameType::FloorType::GRASS3},
            {"Sand", GameType::FloorType::SAND}, {"Water0", GameType::FloorType::WATER0},
            {"Water1", GameType::FloorType::WATER1}, {"Water2", GameType::FloorType::WATER2},
            {"Water3", GameType::FloorType::WATER3}, {"PrettyRoad0", GameType::FloorType::PRETTY_ROAD0},
            {"PrettyRoad1", GameType::FloorType::PRETTY_ROAD1}, {"PrettyRoad2", GameType::FloorType::PRETTY_ROAD2},
            {"PrettyRoad3", GameType::FloorType::PRETTY_ROAD3}, {"PrettyGrass0", GameType::FloorType::PRETTY_GRASS0},
            {"PrettyGrass1", GameType::FloorType::PRETTY_GRASS1}, {"PrettyGrass2", GameType::FloorType::PRETTY_GRASS2},
            {"PrettyGrass3", GameType::FloorType::PRETTY_GRASS3}, {"DeadGrass0", GameType::FloorType::DEAD_GRASS0},
            {"DeadGrass1", GameType::FloorType::DEAD_GRASS1}, {"DeadGrass2", GameType::FloorType::DEAD_GRASS2},
            {"DeadGrass3", GameType::FloorType::DEAD_GRASS3}, {"DarkWater0", GameType::FloorType::DARK_WATER0},
            {"DarkWater1", GameType::FloorType::DARK_WATER1}, {"DarkWater2", GameType::FloorType::DARK_WATER2},
            {"DarkWater3", GameType::FloorType::DARK_WATER3}};
}

void Map::_getTargets(Coordinate center, unsigned int range, std::vector<Coordinate> &targets,
                      bool detectUnreachableTargets) const {
    Coordinate topLeft{}, bottomRight{}, aux{};
    _buildSearchRegion(center, range, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i <= bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j <= bottomRight.jPosition; ++j) {
            if (tiles[i][j].hasMonsterTarget() && !tiles[i][j].isInCity() &&
                (_isReachable({i, j}) || detectUnreachableTargets)) {
                aux.iPosition = i;
                aux.jPosition = j;
                targets.push_back(aux);
            }
        }
    }
}



//////////////////////////////PUBLIC/////////////////////////////

Map::Map(MapFileReader &mapFile, std::list<Coordinate>& priests) {
    CitizenFactory citizenFactory;
    MapSize mapSize = mapFile.getMapDimensions();
    TileInfo aux{};
    std::shared_ptr<Entity> citizen;
    std::unordered_map<std::string, GameType::Entity> entities;
    std::unordered_map<std::string, GameType::Structure> structures;
    std::unordered_map<std::string, GameType::FloorType> floors;
    _initializeConstructorMaps(entities, structures, floors);
    //tiles.resize(mapSize.height, std::vector<Tile>(mapSize.width));
    GameType::Entity auxEntity{};
    for (unsigned int i = 0; i < mapSize.height; ++i) {
        tiles.emplace_back();
        for (unsigned int j = 0; j < mapSize.width; ++j) {
            aux = mapFile.getTileInfo(i, j);
            if (aux.entityType == "Nothing") {
                citizen.reset();
            } else {
                auxEntity = entities.at(aux.entityType);
                citizenFactory.storeCitizen(citizen, auxEntity,
                        {static_cast<int>(i), static_cast<int>(j)});
                if (auxEntity == GameType::PRIEST) {
                    priests.push_back({static_cast<int>(i), static_cast<int>(j)});
                }
            }
            tiles.at(i).emplace_back(aux.isOccupable, aux.isFromCity, floors.at(aux.tileType), structures
                    .at(aux.structureType), std::move(citizen));
        }
    }
}


std::pair<AttackResult, bool> Map::attackTile(int damage, unsigned int level, bool isAPlayer,
                             Coordinate coordinate) {
    return tiles[coordinate.iPosition][coordinate.jPosition].attacked(damage, level, isAPlayer);
}

void Map::getMoveTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets) const {
    _getTargets(center, range, targets, false);
}


void Map::getAttackTargets(Coordinate center, unsigned int range,
                           std::vector<Coordinate> &targets) const {
    _getTargets(center, range, targets, true);
}

bool Map::getPath(Coordinate currentPosition, Coordinate desiredPosition, std::list<Coordinate>& path) const {
    std::priority_queue<PointAndDistance, std::vector<PointAndDistance>, InverseCoordinateDistance> nodes;

    //Key: hijo, Dato: padre
    std::unordered_map<Coordinate, Coordinate> parentsAndChilds;

    //Key:Posicion, Dato: distancia
    std::unordered_map<Coordinate, unsigned int> distances;

    PointAndDistance aux{};
    aux.point = currentPosition;
    aux.distance = 0;
    nodes.push(aux);
    while (!nodes.empty()) {
        aux = nodes.top();
        nodes.pop();
        if (_areCoordinatesEqual(aux.point, desiredPosition)) {
            _storePath(currentPosition, desiredPosition, parentsAndChilds, path);
            return true;
        }
        _storeAdjacentPositions(aux, distances, parentsAndChilds, nodes, desiredPosition);
    }
    return false;
}

void Map::addEntity(Coordinate position, std::shared_ptr<Entity> &&entity) {
    if (!_isCoordinateValid(position)) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    entity->setPosition(position);
    tiles[position.iPosition][position.jPosition].addEntity(std::move(entity));
}

std::shared_ptr<Item> Map::removeItem(Coordinate position) {
    if (!_isCoordinateValid(position)) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    return tiles[position.iPosition][position.jPosition].removeItem();
}

void Map::removeEntity(Coordinate position) {
    if (!_isCoordinateValid(position)) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    tiles[position.iPosition][position.jPosition].removeEntity();
}

void Map::moveEntity(Coordinate startingPosition, Coordinate finalPosition) {
    if ((!_isCoordinateValid(startingPosition)) ||
        (!_isCoordinateValid(finalPosition))) {
        return;
    }
    if (!tiles[finalPosition.iPosition][finalPosition.jPosition].isAvailable()) {
        return;
    }
    Tile& tile = tiles[finalPosition.iPosition][finalPosition.jPosition];
    tile.moveEntity(tiles[startingPosition.iPosition][startingPosition.jPosition],
                        finalPosition);
}

bool Map::isPlaceAvailable(Coordinate position) const {
    return _isCoordinateValid(position) &&
            tiles[position.iPosition][position.jPosition].isAvailable();
}

void Map::addItemsToTile(std::list<std::shared_ptr<Item>>&& items, Coordinate position) {
    if (!_isCoordinateValid(position)) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    tiles[position.iPosition][position.jPosition].addItem(std::move(items));
}

void Map::addItemsToTile(std::shared_ptr<Item> &&item, Coordinate position) {
    if (!_isCoordinateValid(position)) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    tiles[position.iPosition][position.jPosition].addItem(std::move(item));
}


Coordinate Map::getMonsterCoordinate() {
    unsigned int xPosition = Calculator::getRandomInt(0, (int)(tiles.size() - 1));
    unsigned int yPosition = Calculator::getRandomInt(0, (int)(tiles[0].size() - 1));
    while ((!tiles[xPosition][yPosition].isAvailable()) || (tiles[xPosition][yPosition].isInCity())) {
        xPosition = Calculator::getRandomInt(0, (int)(tiles.size() - 1));
        yPosition = Calculator::getRandomInt(0, (int)(tiles[0].size() - 1));
    }
    return {static_cast<int>(xPosition), static_cast<int>(yPosition)};
}

void Map::list(Player &player, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].list(player);
    }
}

void Map::withdraw(Player &player, const std::string &itemName, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].withdraw(player, itemName);
    }
}

void Map::deposit(Player &player, const std::string &itemName, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].deposit(player, itemName);
    }
}

void Map::buy(Player &player, const std::string &itemName, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].buy(player, itemName);
    }
}

void Map::sell(Player &player, const std::string &itemName, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].sell(player, itemName);
    }
}

void Map::operator>>(std::stringstream &mapBuffer) const {
    msgpack::type::tuple<int32_t , int32_t> mapSize(tiles.size(), tiles[0].size());
    msgpack::pack(mapBuffer, mapSize);
    for (const auto & row : tiles) {
        for (const auto & tile : row) {
            tile >> mapBuffer;
        }
    }
}

const Item* Map::peekShowedItemData(Coordinate coordinate) {
    if (!_isCoordinateValid(coordinate)) {
        throw std::invalid_argument("Invalid coordinate in peekShoedItemData");
    }
    return tiles[coordinate.iPosition][coordinate.jPosition].peekShowedItemData();
}

Coordinate Map::getSpawnCoordinateArroundPosition(Coordinate refference) {
    Coordinate topLeft{}, bottomRight{};
    _buildSearchRegion(refference, RESPAWN_RANGE, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i <= bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j <= bottomRight.jPosition; ++j) {
            if (tiles[i][j].isAvailable() && tiles[i][j].isInCity()) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

Coordinate Map::getMonsterRandomPosition(Coordinate refference) const {
    std::vector<Coordinate> positions;
    Coordinate topLeft{}, bottomRight{}, aux{};
    _buildSearchRegion(refference, 1, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i <= bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j <= bottomRight.jPosition; ++j) {
            aux = {i, j};
            if ((refference.calculateDistance(aux) == 1) && (tiles[i][j].isAvailable()) &&
                (!tiles[i][j].isInCity())) {
                positions.push_back(aux);
            }
        }
    }
    if (positions.empty()) {
        return {-1, -1};
    }
    return positions[Calculator::getRandomInt(0, positions.size() - 1)];
}

void Map::requestRestore(Player &player, Coordinate target) {
    if (_isCoordinateValid(target)) {
        tiles[target.iPosition][target.jPosition].requestRestore(player);
    }
}


