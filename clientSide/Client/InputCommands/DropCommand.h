//
// Created by ivan on 9/7/20.
//

#ifndef ARGENTUM_DROPCOMMAND_H
#define ARGENTUM_DROPCOMMAND_H

#include "InputCommand.h"
#include "../../Map/Coordinate.h"

class DropCommand : public InputCommand{
private:
    int32_t slot;
public:
    explicit DropCommand(int32_t slot) : slot(slot) {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_DROPCOMMAND_H
