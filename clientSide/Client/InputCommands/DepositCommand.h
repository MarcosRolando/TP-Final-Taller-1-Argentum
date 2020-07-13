//
// Created by ivan on 10/7/20.
//

#ifndef ARGENTUM_DEPOSITCOMMAND_H
#define ARGENTUM_DEPOSITCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class DepositCommand : public InputCommand{
private:
    Coordinate tile;
    std::string item;

public:
    explicit DepositCommand(Coordinate tile, std::string&& item) : tile(tile), item(item) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_DEPOSITCOMMAND_H
