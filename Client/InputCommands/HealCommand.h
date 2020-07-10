//
// Created by ivan on 10/7/20.
//

#ifndef ARGENTUM_HEALCOMMAND_H
#define ARGENTUM_HEALCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class HealCommand : public InputCommand{
private:
    Coordinate tile;

public:
    explicit HealCommand(Coordinate tile) : tile(tile) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_HEALCOMMAND_H
