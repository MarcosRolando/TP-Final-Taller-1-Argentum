//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_ATTACK_H
#define ARGENTUM_ATTACK_H


#include "Event.h"
#include "../../Map/Coordinate.h"
#include "../../Config/GameEnums.h"

class Entity;

class Attack : public Event {
private:
    Entity& entity;
    Coordinate target{};

public:
    Attack(Entity& _entity, Coordinate _target);
    void operator()(ServerProtocol& protocol) override;

private:
    GameType::Direction _attackDirection(Coordinate attackerPosition) const;
};


#endif //ARGENTUM_ATTACK_H
