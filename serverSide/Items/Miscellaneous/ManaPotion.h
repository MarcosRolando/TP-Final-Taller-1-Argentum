//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_MANAPOTION_H
#define ARGENTUM_MANAPOTION_H


#include "Potion.h"

/*Esta clase representa la pocion de mana que puede consumir el player*/

class ManaPotion: public Potion {
private:
    void restoreStat(Player& player) override;

public:
    explicit ManaPotion(): Potion(GameType::MANA_POTION) {}
    ~ManaPotion() override;
};


#endif //ARGENTUM_MANAPOTION_H
