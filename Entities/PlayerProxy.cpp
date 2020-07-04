//
// Created by marcos on 23/6/20.
//

#include "PlayerProxy.h"
#include "../Map/Coordinate.h"
#include "../Game/Game.h"
#include "../Game/Events/Attack.h"
#include "../Game/Events/Buy.h"
#include "../Game/Events/Sell.h"
#include "../Game/Events/Withdraw.h"
#include "../Game/Events/List.h"
#include "../Entities/Player.h"
#include "../Game/Events/Deposit.h"
#include "../Game/Events/Drop.h"
#include "../Game/Events/Unequip.h"
#include "../Game/Events/UseItem.h"
#include "../Game/Events/Move.h"
#include "../Config/GameEnums.h"

#define MAX_EVENTS_STORED 3


PlayerProxy::PlayerProxy() {
    game = nullptr;
    player = nullptr;
}

PlayerProxy::PlayerProxy(PlayerProxy &&other) noexcept {
    executeMove(std::move(other));
}

PlayerProxy &PlayerProxy::operator=(PlayerProxy &&other) noexcept {
    executeMove(std::move(other));
    return *this;
}


PlayerProxy::PlayerProxy(Game *_game, Player *_player) {
    game = _game;
    player = _player;
}

void PlayerProxy::attack(Coordinate target) {
    if (player->getPosition() != target) {
        if (storedEvents.size() < MAX_EVENTS_STORED) {
            storedEvents.emplace(new Attack(*player, target));
        }
    }
}

void PlayerProxy::useItem(int itemPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new UseItem(*player, itemPosition));
    }
}

void PlayerProxy::meditate() {
    player->meditate();
}

void PlayerProxy::move(GameType::Direction direction) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Move(*game, *player, direction));
    }
}

void PlayerProxy::buyFrom(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Buy(*player, itemName, npcPosition));
    }
}

void PlayerProxy::sellTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Sell(*player, itemName, npcPosition));
    }
}

void PlayerProxy::withdrawFrom(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Withdraw(*player, itemName, npcPosition));
    }
}

void PlayerProxy::listFrom(Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new List(*player, npcPosition));
    }
}

void PlayerProxy::depositTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Deposit(*player, itemName, npcPosition));
    }
}

void PlayerProxy::unequip() {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Unequip(*player));
    }
}

void PlayerProxy::unequip(GameType::EquipmentPlace clothing) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Unequip(*player, clothing));
    }
}

void PlayerProxy::dropItem(unsigned int itemPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Drop(*player, itemPosition));
    }
}

void PlayerProxy::giveEventsToGame() {
    while (!storedEvents.empty()) {
        game->pushEvent(std::move(storedEvents.front()));
        storedEvents.pop();
    }
}

void PlayerProxy::executeMove(PlayerProxy &&other) {
    game = other.game;
    other.game = nullptr;
    player = other.player;
    other.player = nullptr;
    storedEvents = std::move(other.storedEvents);
}

void PlayerProxy::clearMinichat() {
    player->clearMinichat();
}

void PlayerProxy::storeAllRelevantData(std::stringstream& data) const {
    player->storeAllRelevantData(data);
}
