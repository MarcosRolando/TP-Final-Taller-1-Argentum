//
// Created by marcos on 20/6/20.
//

#include "MonsterStats.h"
#include "../Config/Configuration.h"

MonsterStats::MonsterStats() {
    Configuration& config = Configuration::getInstance();
    constitution = config.configMonsterStats();
}
