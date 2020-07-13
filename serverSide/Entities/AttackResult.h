//
// Created by marcos on 18/6/20.
//

#ifndef ARGENTUM_ATTACKRESULT_H
#define ARGENTUM_ATTACKRESULT_H

struct AttackResult {
    int damage;
    unsigned int experience;
    std::string resultMessage;
    bool wasAttackExecuted;
};

#endif //ARGENTUM_ATTACKRESULT_H
