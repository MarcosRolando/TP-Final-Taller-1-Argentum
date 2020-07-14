//
// Created by ivan on 13/7/20.
//

#ifndef ARGENTUM_REQUESTINVENTORYNAMESCOMMAND_H
#define ARGENTUM_REQUESTINVENTORYNAMESCOMMAND_H

#include "InputCommand.h"

class RequestInventoryNamesCommand : public InputCommand{
public:
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_REQUESTINVENTORYNAMESCOMMAND_H
