//
// Created by marcos on 9/7/20.
//

#ifndef ARGENTUM_UPDATEDESTROYITEM_H
#define ARGENTUM_UPDATEDESTROYITEM_H

#include "UpdateEvent.h"
#include "../Map/Coordinate.h"

class UpdateDestroyItem : public UpdateEvent {
private:
    Coordinate position;

public:
    explicit UpdateDestroyItem(Coordinate _position) : position(_position) {}
    void operator()(GameGUI& game) override;
};


#endif //ARGENTUM_UPDATEDESTROYITEM_H
