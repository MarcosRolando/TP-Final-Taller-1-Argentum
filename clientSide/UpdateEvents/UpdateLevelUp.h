//
// Created by marcos on 20/7/20.
//

#ifndef ARGENTUM_UPDATELEVELUP_H
#define ARGENTUM_UPDATELEVELUP_H

#include "UpdateEvent.h"
#include <string>

class UpdateLevelUp : public UpdateEvent {
private:
    std::string playerNickname;
    int level;

public:
    explicit UpdateLevelUp(std::string&& _playerNickname, int _level) :
                playerNickname(std::move(_playerNickname)), level(_level) {}
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATELEVELUP_H
