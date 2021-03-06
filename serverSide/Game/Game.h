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
#include "../../libs/Timer.h"

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

//Esta clase se encarga de manejar en forma general las acciones que quiere realizar
//cada identidad
class Game {
private:
    std::list<Coordinate> priests;
    Map map;
    std::queue<std::unique_ptr<Event>> eventQueue;

    unsigned int monsterCreationRate;
    unsigned int maxNumberOfMonsters;
    unsigned int  spawnInterval;
    Timer monsterSpawnTimer;
    MonstersFactory monstersFactory;

    std::list<Monster*> monsters;
    std::unordered_map<std::string, Player*> players;
    std::unordered_map<Coordinate, const Item*> mapItems;

    std::list<ResurrectData> playersToResurrect;


    friend GameTests;
    friend EntityTests;

private:

    void _removeMonsters(ServerProtocol& protocol);
    void _updateMonsters(double timeStep);
    void _updatePlayers(double timeStep);
    void _executeQueueOperations(ServerProtocol& protocol);
    void _repopulateMap(ServerProtocol& protocol);
    void _updateDeadPlayersTimer(ServerProtocol& protocol, double timestep);

public:

    //Este constructor debe ser utilizado unicamente para las pruebas
    //explicit Game(ClientsMonitor&& clientAux = ClientsMonitor()){};

    explicit Game(MapFileReader&& mapFile);

    //Delega a map el ataque a la coordenada recibida, retorna una instancia de AttackResult junto
    //con un bool que esta en true si se realizo un ataque, sino retorna false
    std::pair<AttackResult, bool> attackPosition(int damage, unsigned int level, bool isAPlayer,
                            Coordinate coordinate);

    //Llama a Map para que guarde los items recibidos en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position);

    //Llama a Map para que guarde el item recibido en el tile que corresponde
    //a la coordenada recibida
    void dropItems(std::shared_ptr<Item>&& item, Coordinate position);

    //Retorna una referencia constante del mapa, util para los monstruos
    const Map& getMap() const;

    //Ejecuta un update del juego, realiza todas las acciones que debe realizar el juego
    //en este tick
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

    //Delega a map el movimiento de la entidad que se encuentra en initialPosition
    //y debe terminar en finalPosition
    void moveEntity(Coordinate initialPosition, Coordinate finalPosition);

    //Game se apropia del puntero al evento, agregandolo a la cola de enentos que
    //despues sera vaciada para ejecutar las acciones del update. Este metodo es
    //virtual para que Fakeit pueda redefinirlo a que no haga nada porque sino la
    //prueba segmentea (el stub no reserva memoria para la cola de eventos creemos)
    virtual void pushEvent(std::unique_ptr<Event>&& event);

    //Crea el player en base al nickname, raza y clase que recibe
    Player& createPlayer(PlayerData& playerData, ServerProtocol& protocol);

    //Carga en el protocolo el estado actual del juego para mandar a un jugador
    //que se conecta y poder mandarle luego solo los cambios en cada update
    const std::vector<char>& getCurrentState(ServerProtocol& protocol);

    //Elimina al jugador del juego, eliminandolo de todos los lugares en los que
    //esta guardado, guarda en el protocolo el mensaje que comunica al resto de los
    //clientes que desaparecio un jugador
    void removePlayer(const std::string& playerNickname, ServerProtocol& protocol);

    //Intenta guardar el item en el inventario del player, retorna el puntero al
    //item que se encuentra al final de la lista de items guardada en el tile del cual
    //se agarro el item, si no hay mas items despues de agarrar uno entonces retorna nullptr
    const Item* storeItemFromTileInPlayer(Player& player);

    //Resusita el player instantaneamente si la coordenada que selecciono contiene un priest, sino
    //guarda su informacion en la lista de players a resucitar para resucitarlo cuando pase la cantidad
    //de tiempo necesaria
    //Si lo resucita instantaneamente retorna true, sino retorna false
    bool requestResurrect(Player& player, Coordinate selectedPosition);

    //Envia un mensaje a otro jugador
    void messagePlayer(Player& playerWhoMessaged, const std::string& playerToMessage, const std::string& message);


    //Retorna true si el player se encuentra en el game, false en caso contrario
    bool playerExists(const std::string& nickname) const;

    //Delega a map el pedido del player al entity de la coordenada target para
    //que se restore su mana y vida
    void requestRestore(Player& player, Coordinate target);

    //Guarda en playerData los items que tiene guardados en el banker el player
    //que tiene el nickname guardado en playerData
    static void getPlayerBank(PlayerData& playerData) ;
};


#endif //ARGENTUM_GAME_H
