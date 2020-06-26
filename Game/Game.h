//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <memory>
#include <queue>
#include "../Map/Map.h"
#include "MonstersFactory.h"
#include "Events/Event.h"
#include "../Server/ClientsMonitor.h"

/*
enum CommandType: char {
    COMMAND_TYPE_MOVE = 'M'
};
*/


class GameTests;
class EntityTests;

struct MoveCommand {
    Coordinate initialPosition;
    Coordinate finalPosition;
    bool isTeleporting;
};

class Game {
private:
    Map map;
    std::queue<std::unique_ptr<Event>> eventQueue;

    unsigned int monsterCreationRate;
    unsigned int maxNumberOfMonsters;
    unsigned int spawnTimer;
    unsigned int  spawnInterval;
    MonstersFactory monstersFactory;

    std::list<std::shared_ptr<Monster>> monsters;
    ClientsMonitor& clients;

    friend GameTests;
    friend EntityTests;

private:

    void _removeEntities();

    void _updateMonsters(double timeStep);

    //CUANDO SE IMPLEMENTE ESTO VAMOS A TENER QUE TOMAR EN CUENTA QUE VAMOS A TENER QUE ENCOLAR
    //CADA MOVIMIENTO REALIZADO PARA MANDARSELO A LOS CLIENTES
    void _executeQueueOperations();
    void _repopulateMap(double timePassed);

public:

    Game(MapFileReader&& mapFile, ClientsMonitor& clients);

    AttackResult attackPosition(int damage, unsigned int level, bool isAPlayer,
                            Coordinate coordinate);

    //Llama a Map para que guarde los items recibidos en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Llama a Map para que guarde el item recibido en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::shared_ptr<Item>&& item, Coordinate position);

    //Retorna una referencia constante del mapa, util para los monstruos
    const Map& getMap() const;

    void update(double timeStep);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    unsigned int list(Player& player, std::list<ProductData>& products, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void withdraw(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void deposit(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void buy(Player& player, const std::string& itemName, Coordinate coordinate);

    //Delega el comportamiento a la entity que guarda, si es que guarda una
    void sell(Player& player, const std::string& itemName, Coordinate coordinate);

    void moveEntity(Coordinate initialPosition, Coordinate finalPosition);

    void pushEvent(std::unique_ptr<Event>&& event);
};


#endif //ARGENTUM_GAME_H
