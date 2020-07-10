//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_SELLCOMMAND_H
#define ARGENTUM_SELLCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class SellCommand : public InputCommand {
private:
    Coordinate tile;
    std::string item;

public:
    explicit SellCommand(Coordinate tile, std::string&& item) : tile(tile), item(item) {}
    void operator()(std::stringstream& msgBuffer) override;
};



#endif //ARGENTUM_SELLCOMMAND_H
