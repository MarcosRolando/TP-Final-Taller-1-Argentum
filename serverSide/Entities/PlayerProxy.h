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
    PlayerProxy();
    PlayerProxy(PlayerProxy&& other) noexcept;
    PlayerProxy& operator=(PlayerProxy&& other) noexcept;
    PlayerProxy(const PlayerProxy& other) = delete;
    PlayerProxy& operator=(const PlayerProxy& other) = delete;
    explicit PlayerProxy(Game* _game, Player* _player);
    void attack(Coordinate target);
    void useItem(int32_t itemPosition);
    void meditate();
    void move(GameType::Direction direction);
    void buyFrom(std::string&& itemName, Coordinate npcPosition);
    void sellTo(std::string&& itemName, Coordinate npcPosition);
    void withdrawFrom(std::string&& itemName, Coordinate npcPosition);
    void messageOtherPlayer(std::string&& playerToMessage, std::string&& message);
    void listFrom(Coordinate npcPosition);
    void depositTo(std::string&& itemName, Coordinate npcPosition);
    void unequip(GameType::EquipmentPlace clothing);
    void dropItem(int32_t itemPosition);
    void pickUpItem();
    void requesResurrect(Coordinate selectedPosition);
    void requestHeal(Coordinate selectedPosition);
    void storeAllRelevantData(std::stringstream& data) const;
    void clearMinichat();
    void giveEventsToGame();

    //Retorna los datos actuales del player
    PlayerData getData() const;

    void remove(ServerProtocol& protocol);
};


#endif //ARGENTUM_PLAYERPROXY_H
