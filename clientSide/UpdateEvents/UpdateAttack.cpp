//
// Created by marcos on 7/7/20.
//

#include "UpdateAttack.h"
#include "../Client/GameGUI.h"
#include <random>

#define ATTACK_HEARING_DISTANCE 6

const float MONSTER_SOUND_PROBABILITY = 0.15;

void UpdateAttack::operator()(GameGUI &game) {
    switch (weapon) {
        case GameType::GNARLED_STAFF:
            game.getMap().addSpell(position, MagicMissile);
            game.getMap().verifyQueueSound(position, Explotion3Sound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::ELVEN_FLUTE:
            game.getMap().addSpell(position, Heal);
            game.getMap().verifyQueueSound(position, HealingSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::LINKED_STAFF:
            game.getMap().addSpell(position, Explosion);
            game.getMap().verifyQueueSound(position, Explotion1Sound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::ASH_ROD:
            game.getMap().addSpell(position, MagicArrow);
            game.getMap().verifyQueueSound(position, Explotion2Sound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::LONGSWORD:
            game.getMap().verifyQueueSound(position, SwordAttackSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::AXE:
            game.getMap().verifyQueueSound(position, Attack2Sound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::WARHAMMER:
            game.getMap().verifyQueueSound(position, HeavyAttackSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::COMPOSITE_BOW:
            game.getMap().addArrow(nickname, position, CompositeArrow);
            game.getMap().verifyQueueSound(position, ArrowSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::SIMPLE_BOW:
            game.getMap().addArrow(nickname, position, SimpleArrow);
            game.getMap().verifyQueueSound(position, ArrowSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::ZOMBIE_ATTACK:
            if (_shouldPlaySound())
                game.getMap().verifyQueueSound(position, ZombieSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::SPIDER_ATTACK:
            if (_shouldPlaySound())
                game.getMap().verifyQueueSound(position, SpiderSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::SKELETON_ATTACK:
            if (_shouldPlaySound())
                game.getMap().verifyQueueSound(position, SkeletonSound, ATTACK_HEARING_DISTANCE);
            break;
        case GameType::GOBLIN_ATTACK:
            if (_shouldPlaySound())
                game.getMap().verifyQueueSound(position, GoblinSound, ATTACK_HEARING_DISTANCE);
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

bool UpdateAttack::_shouldPlaySound() {
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::bernoulli_distribution dist(MONSTER_SOUND_PROBABILITY);
    return dist(generator);
}
