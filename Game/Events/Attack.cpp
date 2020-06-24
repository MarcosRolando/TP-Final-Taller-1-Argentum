//
// Created by agustin on 23/6/20.
//

#include "Attack.h"
#include "../../Entities/Entity.h"

Attack::Attack(Entity& _entity, Coordinate _target) : entity(_entity) {
    target = _target;
}

void Attack::operator()() {
    entity.attack(target);
}
