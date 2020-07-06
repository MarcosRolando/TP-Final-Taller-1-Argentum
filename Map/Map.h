//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_MAP_H
#define ARGENTUM_MAP_H

#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <memory>
#include "InverseCoordinateDistance.h"
#include "Tile.h"

struct AttackResult;
class Item;
class Entity;
class Monster;
class MapFileReader;
class EntityTests;
class MapTests;

class Map {
private:
    std::vector<std::vector<Tile>> tiles;

    friend EntityTests;
    friend MapTests;

private:
    void _storeAdjacentPositions(PointAndDistance refference,
            std::unordered_map<Coordinate, unsigned int>& distances,
            std::unordered_map<Coordinate, Coordinate>& parentsAndChilds,
            std::priority_queue<PointAndDistance, std::vector<PointAndDistance>,
                                InverseCoordinateDistance>& nodes, Coordinate destination) const;
    static unsigned int _getDistance(Coordinate a, Coordinate b);
    bool _isCoordinateValid(Coordinate coordinate) const;
    Coordinate _getValidCoordinate(Coordinate coordinate) const;
    static void _storePath(Coordinate initialPosition, Coordinate desiredPosition, const std::unordered_map<Coordinate,
                           Coordinate>& parentsAndChilds, std::list<Coordinate>& path);
    void _buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topLeft, Coordinate& bottomRight) const;
    static bool _areCoordinatesEqual(Coordinate a, Coordinate b);
    static void _initializeConstructorMaps(std::unordered_map<std::string, GameType::Entity>& entities,
                                           std::unordered_map<std::string, GameType::Structure>& structures,
                                           std::unordered_map<std::string, GameType::FloorType>& floors);
    bool _isReachable(Coordinate position) const;
public:

    //Crea un mapa vacio, de 0x0
    Map() = default;

    explicit Map(MapFileReader& mapFile);

    //Constructor de prueba
    void test(Game& game, std::list<std::shared_ptr<Monster>>& monsters);

    //Ataca la tile y retorna cuanto danio le hizo al entity guardado y el
    // xp ganado, si no hay un etity devuelve 0 en ambos
    AttackResult attackTile(int damage, unsigned int level, bool isAPlayer,
                            Coordinate coordinate);

    //Almacena en el vector la cantidad de targets de un monstruo en un cuadrado centrado en
    //center de lado 2*range+1
    void getTargets(Coordinate center, unsigned int range, std::vector<Coordinate>& targets) const;

    //Almacena en el vector el camino que se debe seguir para llegar a la coordenada deseada
    //Si existe un camino retorna true y la informacion es guardada en path, sino retorna
    //false y no guarda nada
    bool getPath(Coordinate currentPosition, Coordinate desiredPosition, std::list<Coordinate>& path) const;

    //Intenta agregar la entity al tile que se encuentra en la coordenada recibida apropiandose
    //del shared_ptr, si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    //Si la posicion es ocupable entonces se apropia del puntero, sino tira TPException
    void addEntity(Coordinate position, std::shared_ptr<Entity>&& entity);

    //Toma el primer item almacenado en el tile que se encuentra en la coordenada
    //pasada, lo elimina de la tile y lo retorna, si la coordenada es invalida se
    //tira una exception de invalid_argument
    //Si el tile no tiene items retorna un shared_ptr que almacena nullptr
    std::shared_ptr<Item> removeItem(Coordinate position);

    //Elimina la entity almacenada en la coordenada, liberando sus recursos y permitiendo
    //el almacenamiento de otra entity, si la coordenada es invalida tira invalid_argument
    void removeEntity(Coordinate position);

    //Intenta mover la entity de starting a final position, si finalPosition esta ocupada
    //entonces retorna false, sino retorna true
    //Si alguna de las coordenadas es invalida tira invalid_argument
    void moveEntity(Coordinate startingPosition, Coordinate finalPosition);

    //Retorna true si el lugar puede ser ocupado por una entity, false en caso contrario
    bool isPlaceAvailable(Coordinate position) const;

    //Agrega los items de la lista al tile al tile que se encuentra en la coordenada recibida apropiandose de la lista,
    //si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    //Se pueden guardar smart_pointers que contengan nullptr, pero no se deberia hacer, el chequeo
    //de si se esta guardando null o no tiene que venir de afuera
    void addItemsToTile(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Agrega el item al tile que se encuentra en la coordenada recibida apropiandose del shared_ptr,
    //si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    //Se pueden guardar smart_pointers que contengan nullptr, pero no se deberia hacer, el chequeo
    //de si se esta guardando null o no tiene que venir de afuera
    void addItemsToTile(std::shared_ptr<Item>&& item, Coordinate position);

    //Retorna una coordenada aleatoria en la que puede ponerse un monstruo
    Coordinate getMonsterCoordinate();

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    //unsigned int list(Player& player, std::list<ProductData>& products, Coordinate coordinate);
    void list(Player& player, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void withdraw(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void deposit(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void buy(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void sell(Player& player, const std::string& itemName, Coordinate coordinate);

    void operator>>(std::stringstream& mapBuffer) const;

    //Saca del tile el item que se le muestra a los jugadores y lo retorna
    std::shared_ptr<Item> getItemFromTile(Coordinate coordinate);

    //Retorna un pair que almacena el tipo del item y su id, si la coordenada es inexistente
    //guarda -2 en el id (second), si el tile no tiene items guarda -1, sino guarda el it del item
    std::pair<GameType::ItemType, int32_t> peekShowedItemData(Coordinate coordinate);

};


#endif //ARGENTUM_MAP_H
