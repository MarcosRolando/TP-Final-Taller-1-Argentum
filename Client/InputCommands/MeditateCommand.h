//
// Created by ivan on 7/7/20.
//

#ifndef ARGENTUM_MEDITATECOMMAND_H
#define ARGENTUM_MEDITATECOMMAND_H

#include "InputCommand.h"

class MeditateCommand : public InputCommand{
public:
    MeditateCommand() {}
    void operator()(std::stringstream& msgBuffer) override;
};


#endif //ARGENTUM_MEDITATECOMMAND_H
