//
// Created by marcos on 7/7/20.
//

#include "UpdateAttack.h"
#include "../Client/GameGUI.h"

void UpdateAttack::operator()(GameGUI &game) {
    switch (weapon) {
        case GameType::GNARLED_STAFF:
            game.getMap().addSpell(position, MagicMissile);
            game.getMap().verifyQueueSound(position, Explotion3Sound, 6);
            break;
        case GameType::ELVEN_FLUTE:
            game.getMap().addSpell(position, Heal);
            game.getMap().verifyQueueSound(position, HealingSound, 6);
            break;
        case GameType::LINKED_STAFF:
            game.getMap().addSpell(position, Explosion);
            game.getMap().verifyQueueSound(position, Explotion1Sound, 6);
            break;
        case GameType::ASH_ROD:
            game.getMap().addSpell(position, MagicArrow);
            game.getMap().verifyQueueSound(position, Explotion2Sound, 6);
            break;
        case GameType::LONGSWORD:
            game.getMap().verifyQueueSound(position, SwordAttackSound, 6);
            break;
        case GameType::AXE:
            game.getMap().verifyQueueSound(position, Attack2Sound, 6);
            break;
        case GameType::WARHAMMER:
            game.getMap().verifyQueueSound(position, HeavyAttackSound, 6);
            break;
        case GameType::COMPOSITE_BOW:
            game.getMap().addArrow(nickname, position, CompositeArrow);
            game.getMap().verifyQueueSound(position, ArrowSound, 6);
            break;
        case GameType::SIMPLE_BOW:
            game.getMap().addArrow(nickname, position, SimpleArrow);
            game.getMap().verifyQueueSound(position, ArrowSound, 6);
        case GameType::ZOMBIE_ATTACK:
            game.getMap().verifyQueueSound(position, ZombieSound, 6);
            break;
        case GameType::SPIDER_ATTACK:
            game.getMap().verifyQueueSound(position, SpiderSound, 6);
            break;
        default:
            break;
    }
    game.getMap().changeEntityLookDirection(nickname, attackDir);
}

UpdateAttack::UpdateAttack(std::string& _nickname, Coordinate _position,
                        int32_t _weapon, GameType::Direction _attackDir) {
    nickname = std::move(_nickname);
    position = _position;
    weapon = static_cast<GameType::Weapon>(_weapon);
    attackDir = _attackDir;
}
