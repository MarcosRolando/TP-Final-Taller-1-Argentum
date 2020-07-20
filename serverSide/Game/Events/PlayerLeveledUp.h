//
// Created by agustin on 20/7/20.
//

#ifndef ARGENTUM_PLAYERLEVELEDUP_H
#define ARGENTUM_PLAYERLEVELEDUP_H


#include "Event.h"

#include <string>

class PlayerLeveledUp: public Event {
private:
    const std::string& playerNickname;
    int32_t level;

public:
    explicit PlayerLeveledUp(const std::string& playerNickname, int32_t level);

    void operator()(ServerProtocol& protocol) override;
};


#endif //ARGENTUM_PLAYERLEVELEDUP_H
