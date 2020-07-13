//
// Created by marcos on 7/5/20.
//

#ifndef ARGENTUM_UPDATEPLAYERDEATH_H
#define ARGENTUM_UPDATEPLAYERDEATH_H

#include "UpdateEvent.h"
#include <string>

class UpdatePlayerDeath : public UpdateEvent {
private:
    std::string nickname;

public:
    explicit UpdatePlayerDeath(std::string&& _nickname) : nickname(std::move(_nickname)) {}
    void operator()(GameGUI& game);
};


#endif //ARGENTUM_UPDATEPLAYERDEATH_H
