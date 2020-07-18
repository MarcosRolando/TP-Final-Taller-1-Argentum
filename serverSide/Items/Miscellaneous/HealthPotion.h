//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_HEALTHPOTION_H
#define ARGENTUM_HEALTHPOTION_H


#include "Potion.h"

/*Esta clase representa la pocion de vida que puede consumir el player*/

class HealthPotion: public Potion {
private:
    void restoreStat(Player& player) override;
public:
    explicit HealthPotion(): Potion(GameType::HEALTH_POTION) {}
    ~HealthPotion() override;
};


#endif //ARGENTUM_HEALTHPOTION_H
