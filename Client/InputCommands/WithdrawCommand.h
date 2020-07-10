//
// Created by ivan on 10/7/20.
//

#ifndef ARGENTUM_WITHDRAWCOMMAND_H
#define ARGENTUM_WITHDRAWCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class WithdrawCommand : public InputCommand{
private:
    Coordinate tile;
    std::string item;

public:
    explicit WithdrawCommand(Coordinate tile, std::string&& item) : tile(tile), item(item) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_WITHDRAWCOMMAND_H
