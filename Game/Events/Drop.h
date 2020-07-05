//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_DROP_H
#define ARGENTUM_DROP_H


#include "Event.h"

#include <string>
#include <memory>
#include <list>
#include "../../Items/Item.h"
#include "../../Map/Coordinate.h"

class ServerProtocol;
class Player;
class Game;

class Drop: public Event {
private:
    Player* player{nullptr};
    int position{-1};

    std::list<std::shared_ptr<Item>> items;
    Game* game{nullptr};
    Coordinate dropPosition{-1, -1};

public:
    Drop(Player& player, int position);

    //La lista debe contener al menos 1 elemento si se utiliza este contrsuctor
    Drop(Game& game, std::list<std::shared_ptr<Item>>&& items, Coordinate dropPosition);
    Drop(Game& game, std::shared_ptr<Item>&& item, Coordinate dropPosition);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_DROP_H
