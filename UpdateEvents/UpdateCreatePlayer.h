//
// Created by ivan on 1/7/20.
//

#ifndef ARGENTUM_UPDATECREATEPLAYER_H
#define ARGENTUM_UPDATECREATEPLAYER_H

#include "UpdateEvent.h"
#include <string>
#include "../Shared/GameEnums.h"

class UpdateCreatePlayer : public UpdateEvent{
private:

public:
    UpdateCreatePlayer();
    void operator()() override;
};


#endif //ARGENTUM_UPDATECREATEPLAYER_H
