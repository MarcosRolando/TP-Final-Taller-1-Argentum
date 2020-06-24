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

void PlayerProxy::attack(Coordinate target) {
    std::unique_ptr<Attack> event(new Attack(player, target));
    game.pushEvent(std::move(event));
}

void PlayerProxy::useItem(int itemPosition) {

}

void PlayerProxy::meditate() {
    player.meditate();
}

void PlayerProxy::move(Direction direction) {
    player.requestMove(direction);
}

void PlayerProxy::buyFrom(std::string &&itemName, Coordinate npcPosition) {
    std::unique_ptr<Buy> event(new Buy(player, itemName, npcPosition));
    game.pushEvent(std::move(event));
}

void PlayerProxy::sellTo(std::string &&itemName, Coordinate npcPosition) {
    std::unique_ptr<Sell> event(new Sell(player, itemName, npcPosition));
    game.pushEvent(std::move(event));
}

void PlayerProxy::withdrawFrom(std::string &&itemName, Coordinate npcPosition) {
    std::unique_ptr<Withdraw> event(new Withdraw(player, itemName, npcPosition));
    game.pushEvent(std::move(event));
}

void PlayerProxy::listFrom(Coordinate npcPosition) {
    std::unique_ptr<List> event(new List(player, npcPosition));
    game.pushEvent(std::move(event));
}

void PlayerProxy::depositTo(std::string &&itemName, Coordinate npcPosition) {
    std::unique_ptr<Deposit> event(new Deposit(player, itemName, npcPosition));
    game.pushEvent(std::move(event));
}

void PlayerProxy::unequip() {
    std::unique_ptr<Deposit> event(new Deposit(player, itemName, npcPosition));
    game.pushEvent(std::move(event));
}
