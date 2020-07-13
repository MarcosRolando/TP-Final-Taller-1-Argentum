//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_BUYCOMMAND_H
#define ARGENTUM_BUYCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class BuyCommand : public InputCommand{
private:
    Coordinate tile;
    std::string item;

public:
    explicit BuyCommand(Coordinate tile, std::string&& item) : tile(tile), item(item) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_BUYCOMMAND_H
