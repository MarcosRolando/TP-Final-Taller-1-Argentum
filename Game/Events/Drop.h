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

class Player;

class Drop: public Event {
private:
<<<<<<< HEAD
    Player* player;
=======
    Player* player{nullptr};
>>>>>>> bc254ece2fc1c263b97ad72353f9195db38e0954
    unsigned int position;
    std::list<std::shared_ptr<Item>> items;

public:
    Drop(Player& player, unsigned int position);
    Drop(std::list<std::shared_ptr<Item>>&& items, unsigned int position);
    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_DROP_H
