//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_LISTCOMMAND_H
#define ARGENTUM_LISTCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class ListCommand : public InputCommand{
private:
    Coordinate tile;

public:
    explicit ListCommand(Coordinate tile) : tile(tile) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_LISTCOMMAND_H
