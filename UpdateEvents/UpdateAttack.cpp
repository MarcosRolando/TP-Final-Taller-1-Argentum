//
// Created by marcos on 7/7/20.
//

#include "UpdateAttack.h"
#include "../Client/GameGUI.h"

void UpdateAttack::operator()(GameGUI &game) {
    switch (weapon) {
        case GameType::GNARLED_STAFF:
            game.getMap().addSpell(position, MagicMissile);
            game.getMap().verifyQueueSound(position, Explotion3, 6);
            break;
        case GameType::ELVEN_FLUTE:
            game.getMap().addSpell(position, Heal);
            break;
        case GameType::LINKED_STAFF:
            game.getMap().addSpell(position, Explosion);
            game.getMap().verifyQueueSound(position, Explotion1, 6);
            break;
        case GameType::ASH_ROD:
            game.getMap().addSpell(position, MagicArrow);
            game.getMap().verifyQueueSound(position, Explotion2, 6);
            break;
        case GameType::LONGSWORD:
            game.getMap().verifyQueueSound(position, SwordAttack, 6);
            break;
        case GameType::SIMPLE_BOW:
            game.getMap().verifyQueueSound(position, Arrow, 6);
        default:
            break;
    }
}

UpdateAttack::UpdateAttack(Coordinate _position, int32_t _weapon) {
    position = _position;
    weapon = static_cast<GameType::Weapon>(_weapon);
}
