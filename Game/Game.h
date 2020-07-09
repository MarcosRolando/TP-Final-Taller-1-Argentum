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
#include "../Items/ItemData.h"
#include "ResurrectData.h"

class EntityTests;
struct PlayerData;

class PlayerShouldBeRemoved {
private:
    Player* playerToRemove;

public:
    explicit PlayerShouldBeRemoved(Player* player) : playerToRemove(player) {}
    bool operator()(const Player* player);
};

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

    std::list<Monster*> monsters;
    std::unordered_map<const std::string*, Player*> players;
    std::unordered_map<Coordinate, const Item*> mapItems;

    std::list<Coordinate> priests;
    std::list<ResurrectData> playersToResurrect;


    friend GameTests;
    friend EntityTests;

private:

    void _removeMonsters(ServerProtocol& protocol);

    void _updateMonsters(double timeStep);

    void _updatePlayers(double timeStep);

    //CUANDO SE IMPLEMENTE ESTO VAMOS A TENER QUE TOMAR EN CUENTA QUE VAMOS A TENER QUE ENCOLAR
    //CADA MOVIMIENTO REALIZADO PARA MANDARSELO A LOS CLIENTES
    void _executeQueueOperations(ServerProtocol& protocol);
    void _repopulateMap(double timePassed, ServerProtocol& protocol);
    void _updateDeadPlayersTimer(ServerProtocol& protocol, double timestep);

public:

    //Este constructor debe ser utilizado unicamente para las pruebas
    //explicit Game(ClientsMonitor&& clientAux = ClientsMonitor());

    explicit Game(MapFileReader&& mapFile);

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

    void update(double timeStep, ServerProtocol& protocol);

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

    void moveEntity(Coordinate initialPosition, Coordinate finalPosition);

    void pushEvent(std::unique_ptr<Event>&& event);

    /*Crea el player en base al nickname, raza y clase que recibe*/
    Player& createPlayer(PlayerData& playerData, ServerProtocol& protocol);

    const std::vector<char>& getCurrentState(ServerProtocol& protocol);

    void removePlayer(Player* player, ServerProtocol& protocol);

    //Intenta guardar el item en el inventario del player, retorna el puntero al
    //item que se encuentra al final de la lista de items guardada en el tile del cual
    //se agarro el item, si no hay mas items despues de agarrar uno entonces retorna nullptr
    const Item* storeItemFromTileInPlayer(Player& player);

    //Resusita el player instantaneamente si la coordenada que selecciono contiene un priest, sino
    //guarda su informacion para resucitarlo cuando la cantidad de tiempo necesaria
    //Si lo resucita retorna true, sino retorna false
    bool requestResurrect(Player& player, Coordinate selectedPosition);
};


#endif //ARGENTUM_GAME_H
