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

class Tile;
struct AttackResult;
class Item;
class Entity;
class Monster;

class Map {
private:
    std::vector<std::vector<Tile>> tiles;

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
    void _buildSearchRegion(Coordinate center, unsigned int range, Coordinate& topRight, Coordinate& bottomLeft) const;
    static bool _areCoordinatesEqual(Coordinate a, Coordinate b);
public:
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
    //Si la posicion es ocupable entonces se apropia del puntero y retorna true,
    //sino no se apropia de de el y retorna false
    bool addEntity(Coordinate position, std::shared_ptr<Entity>&& entity);

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
    bool moveEntity(Coordinate startingPosition, Coordinate finalPosition);

    //Retorna true si el lugar puede ser ocupado por una entity, false en caso contrario
    bool isPlaceAvailable(Coordinate position) const;

    //Agrega los items de la lista al tile al tile que se encuentra en la coordenada recibida apropiandose de la lista,
    //si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    void addItemsToTile(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Agrega el item al tile que se encuentra en la coordenada recibida apropiandose del shared_ptr,
    //si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    void addItemsToTile(std::shared_ptr<Item>&& item, Coordinate position);

    //Retorna una coordenada aleatoria en la que puede ponerse un monstruo
    Coordinate getMonsterCoordinate(/*std::shared_ptr<Monster>&& monster*/);
};


#endif //ARGENTUM_MAP_H
