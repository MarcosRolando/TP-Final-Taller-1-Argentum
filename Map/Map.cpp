//
// Created by agustin on 7/6/20.
//

#include <queue>
#include <unordered_map>
#include <memory>
#include "Map.h"
#include "../AttackResult.h"
#include "../Config/Calculator.h"

//todo ESTO ES DE PRUEBA
#include "../Config/GameEnums.h"
#include "../Entities/Monster.h"
#include "../Entities/Player.h"
#include "../Items/Defense/Chest.h"
#include "../Items/Defense/Head.h"
#include "../Items/Defense/Shield.h"

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

void Map::_buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft) const {
    Coordinate aux{};
    aux.iPosition = static_cast<int>(center.iPosition - range);
    aux.jPosition = static_cast<int>(center.jPosition - range);
    topRight = _getValidCoordinate(aux);
    aux.iPosition = static_cast<int>(center.iPosition + range);
    aux.jPosition = static_cast<int>(center.jPosition + range);
    bottomLeft = _getValidCoordinate(aux);
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
            if ((aux.distance == 1) && ((tiles[i][j].isAvailable()) || tiles[i][j].hasMonsterTarget())) {
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


//////////////////////////////PUBLIC/////////////////////////////


AttackResult Map::attackTile(int damage, unsigned int level, bool isAPlayer,
                             Coordinate coordinate) {
    return tiles[coordinate.iPosition][coordinate.jPosition].attacked(damage, level, isAPlayer);
}

void Map::getTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets) const {
    Coordinate topLeft{}, bottomRight{}, aux{};
    _buildSearchRegion(center, range, topLeft, bottomRight);
    for (int i = topLeft.iPosition; i < bottomRight.iPosition; ++i) {
        for (int j = topLeft.jPosition; j < bottomRight.jPosition; ++j) {
            if (tiles[i][j].hasMonsterTarget()) {
                aux.iPosition = i;
                aux.jPosition = j;
                targets.push_back(aux);
            }
        }
    }
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

bool Map::moveEntity(Coordinate startingPosition, Coordinate finalPosition) {
    if ((!_isCoordinateValid(startingPosition)) ||
        (!_isCoordinateValid(finalPosition))) {
        throw (std::invalid_argument("Out of bounds coordinate"));
    }
    if (!tiles[finalPosition.iPosition][finalPosition.jPosition].isAvailable()) {
        return false;
    }
    Tile& tile = tiles[finalPosition.iPosition][finalPosition.jPosition];
    tile.moveEntity(std::move(tiles[startingPosition.iPosition][startingPosition.jPosition]),
                        finalPosition);
    return true;
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

Coordinate Map::getMonsterCoordinate(/*std::shared_ptr<Monster>&& monster*/) {
    //std::shared_ptr<Entity> aux;
    //aux.reset((Entity*)monster.get());
    //monster.reset();
    unsigned int xPosition = Calculator::getRandomInt(0, (int)(tiles.size() - 1));
    unsigned int yPosition = Calculator::getRandomInt(0, (int)(tiles[0].size() - 1));
    while ((!tiles[xPosition][yPosition].isAvailable()) || (tiles[xPosition][yPosition].isInCity())) {
        xPosition = Calculator::getRandomInt(0, (int)(tiles.size() - 1));
        yPosition = Calculator::getRandomInt(0, (int)(tiles[0].size() - 1));
    }
    //tiles[xPosition][yPosition].addEntity(std::static_pointer_cast<Entity>(monster));
    return {static_cast<int>(xPosition), static_cast<int>(yPosition)};
}


void Map::test(Game& game, std::list<std::shared_ptr<Monster>>& monsters) {
    for (int i = 0; i < 100; ++i) {
        tiles.emplace_back();
        for (int j = 0; j < 100; ++j) {
            tiles[i].emplace_back(false, FLOOR_TYPE_GRASS);
        }
    }
    /*
    std::shared_ptr<Monster> monster1(new Monster(game, {0,0}, GameType::SPIDER));
    std::shared_ptr<Monster> monster2(new Monster(game, {3,2}, GameType::GOBLIN));
    std::shared_ptr<Monster> monster3(new Monster(game, {5,5}, GameType::ZOMBIE));

    std::shared_ptr<Player> player1(new Player(game, GameType::HUMAN,
            GameType::WIZARD, 3, 0, {1, 2}, "agusputo"));
    std::shared_ptr<Item> armour(new Chest(GameType::PLATE_ARMOR));
    std::shared_ptr<Item> helmet(new Head(GameType::IRON_HELMET));
    std::shared_ptr<Item> shield(new Shield(GameType::IRON_SHIELD));
    player1->storeItem(std::move(armour));
    player1->storeItem(std::move(helmet));
    player1->storeItem(std::move(shield));
    player1->useItem(0);
    player1->useItem(1);
    player1->useItem(2);
    std::shared_ptr<Player> player2(new Player(game, GameType::HUMAN,
                                              GameType::WIZARD, 3, 0, {2, 2}, "agusputo"));
    armour.reset(new Chest(GameType::PLATE_ARMOR));
    helmet.reset(new Head(GameType::IRON_HELMET));
    shield.reset(new Shield(GameType::IRON_SHIELD));
    player2->storeItem(std::move(armour));
    player2->storeItem(std::move(helmet));
    player2->storeItem(std::move(shield));
    player2->useItem(0);
    player2->useItem(1);
    player2->useItem(2);
    std::shared_ptr<Player> player3(new Player(game, GameType::HUMAN,
                                              GameType::WIZARD, 3, 0, {4, 5}, "agusputo"));
    armour.reset(new Chest(GameType::PLATE_ARMOR));
    helmet.reset(new Head(GameType::IRON_HELMET));
    shield.reset(new Shield(GameType::IRON_SHIELD));
    player3->storeItem(std::move(armour));
    player3->storeItem(std::move(helmet));
    player3->storeItem(std::move(shield));
    player3->useItem(0);
    player3->useItem(1);
    player3->useItem(2);
    monsters.push_front(monster1);
    monsters.push_front(monster2);
    monsters.push_front(monster3);
    tiles[0][0].addEntity(std::move(monster1));
    tiles[3][2].addEntity(std::move(monster2));
    tiles[5][5].addEntity(std::move(monster3));
    tiles[1][2].addEntity(std::move(player1));
    tiles[2][2].addEntity(std::move(player2));
    tiles[4][5].addEntity(std::move(player3));
     */
}

unsigned int Map::list(Player &player, std::list<ProductData> &products, Coordinate coordinate) {
    if (!_isCoordinateValid(coordinate)) {
        return 0;
    }
    return tiles[coordinate.iPosition][coordinate.jPosition].list(player, products);
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
        tiles[coordinate.iPosition][coordinate.jPosition].deposit(player, itemName);
    }
}

void Map::sell(Player &player, const std::string &itemName, Coordinate coordinate) {
    if (_isCoordinateValid(coordinate)) {
        tiles[coordinate.iPosition][coordinate.jPosition].sell(player, itemName);
    }
}
