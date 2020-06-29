//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEEVENT_H
#define ARGENTUM_UPDATEEVENT_H

/*Interfaz, los eventos que updatean el juego deben implmenetar cada caso*/

class UpdateEvent {
public:
    virtual void operator()() = 0;
};


#endif //ARGENTUM_UPDATEEVENT_H
