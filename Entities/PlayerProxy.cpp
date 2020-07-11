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
#include "../Game/Events/PickUpItem.h"
#include "../Game/Events/RequestResurrect.h"
#include "../Game/Events/Message.h"
#include "../Game/Events/RestoreStats.h"

#define MAX_EVENTS_STORED 3


PlayerProxy::PlayerProxy() {
    game = nullptr;
    player = nullptr;
}

PlayerProxy::PlayerProxy(PlayerProxy &&other) noexcept {
    game = other.game;
    other.game = nullptr;
    player = other.player;
    other.player = nullptr;
    storedEvents = std::move(other.storedEvents);
}

PlayerProxy &PlayerProxy::operator=(PlayerProxy &&other) noexcept {
    game = other.game;
    other.game = nullptr;
    player = other.player;
    other.player = nullptr;
    storedEvents = std::move(other.storedEvents);
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
#include <iostream>
void PlayerProxy::useItem(int32_t itemPosition) {
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
        storedEvents.emplace(new Buy(*player, std::move(itemName), npcPosition));
    }
}

void PlayerProxy::sellTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Sell(*player, std::move(itemName), npcPosition));
    }
}

void PlayerProxy::withdrawFrom(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Withdraw(*player, std::move(itemName), npcPosition));
    }
}

void PlayerProxy::listFrom(Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new List(*player, npcPosition));
    }
}

void PlayerProxy::depositTo(std::string &&itemName, Coordinate npcPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Deposit(*player, std::move(itemName), npcPosition));
    }
}

void PlayerProxy::unequip(GameType::EquipmentPlace place) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Unequip(*player, place));
    }
}

void PlayerProxy::dropItem(int32_t itemPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Drop(*player, itemPosition));
    }
}

void PlayerProxy::pickUpItem() {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new PickUpItem(*game, *player));
    }
}

void PlayerProxy::requesResurrect(Coordinate selectedPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new RequestResurrect(*game, *player, selectedPosition));
    }
}

void PlayerProxy::messageOtherPlayer(std::string &&playerToMessage, std::string &&message) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new Message(*game, *player, std::move(playerToMessage),
                                         std::move(message)));
    }
}

void PlayerProxy::requestHeal(Coordinate selectedPosition) {
    if (storedEvents.size() < MAX_EVENTS_STORED) {
        storedEvents.emplace(new RestoreStats(*game, *player, selectedPosition));
    }
}

void PlayerProxy::giveEventsToGame() {
    while (!storedEvents.empty()) {
        game->pushEvent(std::move(storedEvents.front()));
        storedEvents.pop();
    }
}

void PlayerProxy::clearMinichat() {
    player->clearMinichat();
}

void PlayerProxy::storeAllRelevantData(std::stringstream& data) const {
    player->storeAllRelevantData(data);
}

void PlayerProxy::remove(ServerProtocol& protocol) {
    game->removePlayer(player, protocol);
}

