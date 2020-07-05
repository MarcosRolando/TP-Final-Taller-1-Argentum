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
    void useItem(int itemPosition);
    void meditate();
    void move(GameType::Direction direction);
    void buyFrom(std::string&& itemName, Coordinate npcPosition);
    void sellTo(std::string&& itemName, Coordinate npcPosition);
    void withdrawFrom(std::string&& itemName, Coordinate npcPosition);
    void listFrom(Coordinate npcPosition);
    void depositTo(std::string&& itemName, Coordinate npcPosition);
    void unequip();
    void unequip(GameType::EquipmentPlace clothing);
    void dropItem(unsigned int itemPosition);
    void storeAllRelevantData(std::stringstream& data) const;
    void clearMinichat();
    void giveEventsToGame();

    void remove(ServerProtocol& protocol);

private:
    void executeMove(PlayerProxy&& other);
};


#endif //ARGENTUM_PLAYERPROXY_H
