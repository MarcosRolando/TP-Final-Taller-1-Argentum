//
// Created by agustin on 7/6/20.
//

#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H


#include "../Map/Map.h"
#include "MonstersFactory.h"
#include <queue>

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
    std::queue<MoveCommand> eventQueue;

    unsigned int monsterCreationRate;
    unsigned int maxNumberOfMonsters;
    unsigned int spawnTimer;
    unsigned int  spawnInterval;
    MonstersFactory monstersFactory;

    std::list<std::shared_ptr<Monster>> monsters;

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

    Game();

    AttackResult attackPosition(int damage, unsigned int level, bool isAPlayer,
                            Coordinate coordinate);

    //Llama a Map para que guarde los items recibidos en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Llama a Map para que guarde el item recibido en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::shared_ptr<Item>&& item, Coordinate position);

    //Le indica a game que se quiere mover un entity de initial a final position,
    //initialPosition debe contener un entity, sino el comportamiento es indefinido,
    //si finalPosition no es ocupable entonces no hace nada eventualmente
    //Esta funcion encola la accion de mover un entity de initial a finalPosition
    void requestMove(Coordinate initialPosition, Coordinate finalPosition);

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
};


#endif //ARGENTUM_GAME_H
