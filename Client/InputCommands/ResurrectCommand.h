//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_RESURRECTCOMMAND_H
#define ARGENTUM_RESURRECTCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class ResurrectCommand : public InputCommand {
private:
    Coordinate tile;

public:
    explicit ResurrectCommand(Coordinate tile) : tile(tile) {}
    void operator()(std::stringstream& msgBuffer) override;
};



#endif //ARGENTUM_RESURRECTCOMMAND_H
