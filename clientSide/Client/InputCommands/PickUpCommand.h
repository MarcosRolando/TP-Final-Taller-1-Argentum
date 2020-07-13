//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_PICKUPCOMMAND_H
#define ARGENTUM_PICKUPCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class PickUpCommand : public InputCommand{
public:
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_PICKUPCOMMAND_H
