//
// Created by marcos on 23/6/20.
//

#ifndef ARGENTUM_PLAYERPROXY_H
#define ARGENTUM_PLAYERPROXY_H

#include <string>
#include <queue>
#include "../Items/Inventory.h"
#include "../Game/Events/Event.h"

class Player;
class Game;
struct Coordinate;

class PlayerProxy {
private:
    Game* game{nullptr};
    Player* player{nullptr};
    std::queue<std::unique_ptr<Event>> storedEvents;

public:
    PlayerProxy() = default;
    PlayerProxy(PlayerProxy&& other) noexcept;
    PlayerProxy& operator=(PlayerProxy&& other) noexcept;
    PlayerProxy(const PlayerProxy& other) = delete;
    PlayerProxy& operator=(const PlayerProxy& other) = delete;
    explicit PlayerProxy(Game* _game, Player* _player);

    /*Encola un ataque*/
    void attack(Coordinate target);

    /*Encola un use item (equipar para los equipables, consumir para los consumibles, etc)*/
    void useItem(int32_t itemPosition);

    /*Setea al player en modo meditacion (es el unico evento que no encolamos
     * porque no valia la pena*/
    void meditate();

    /*Encola un buy*/
    void buyFrom(std::string&& itemName, Coordinate npcPosition);

    /*Encola un sell*/
    void sellTo(std::string&& itemName, Coordinate npcPosition);

    /*Encola un withdraw*/
    void withdrawFrom(std::string&& itemName, Coordinate npcPosition);

    /*Encola un mensaje a otro player*/
    void messageOtherPlayer(std::string&& playerToMessage, std::string&& message);

    /*Encola un list*/
    void listFrom(Coordinate npcPosition);

    /*Encola un deposit*/
    void depositTo(std::string&& itemName, Coordinate npcPosition);

    /*Encola un unequip*/
    void unequip(GameType::EquipmentPlace clothing);

    /*Encola un drop item*/
    void dropItem(int32_t itemPosition);

    /*Encola un pickup de un item*/
    void pickUpItem();

    /*Encola un resurrect*/
    void requesResurrect(Coordinate selectedPosition);

    /*Encola un heal*/
    void requestHeal(Coordinate selectedPosition);

    /*Encola un request para ver el nombre de los items del inventario*/
    void getInventoryNames();

    /*Guarda en data los datos del player administrado por este PlayerProxy*/
    void storeAllRelevantData(std::stringstream& data) const;

    /*Borra el minichat del player*/
    void clearMinichat();

    /*Mergea la cola del PlayerProxy con la del Game*/
    void giveEventsToGame();

    /*Encola el comando para empezar a moverse en una direccion*/
    void startMoving(GameType::Direction direction);

    /*Encola la directiva para dejar de moverse*/
    void stopMoving();

    /*Retorna los datos actuales del player*/
    PlayerData getData() const;
};


#endif //ARGENTUM_PLAYERPROXY_H
