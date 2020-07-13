//
// Created by marcos on 7/3/20.
//

#ifndef ARGENTUM_UPDATEREMOVEENTITY_H
#define ARGENTUM_UPDATEREMOVEENTITY_H

#include "UpdateEvent.h"
#include <string>

class UpdateRemoveEntity : public UpdateEvent {
private:
    std::string nickname;

public:
    explicit UpdateRemoveEntity(std::string&& _nickname) : nickname(_nickname) {}
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEREMOVEENTITY_H
