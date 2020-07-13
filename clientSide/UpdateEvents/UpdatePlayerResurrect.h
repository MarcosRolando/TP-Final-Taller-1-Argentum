//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_UPDATEPLAYERRESURRECT_H
#define ARGENTUM_UPDATEPLAYERRESURRECT_H

#include "UpdateEvent.h"
#include <string>

class UpdatePlayerResurrect : public UpdateEvent {
private:
    std::string nickname;

public:
    explicit UpdatePlayerResurrect(std::string&& _nickname) : nickname(std::move(_nickname)) {}
    void operator()(GameGUI& game);
};


#endif //ARGENTUM_UPDATEPLAYERRESURRECT_H
