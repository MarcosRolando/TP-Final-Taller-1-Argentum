//
// Created by marcos on 6/29/20.
//

#ifndef ARGENTUM_UPDATEEVENT_H
#define ARGENTUM_UPDATEEVENT_H

/*Interfaz, los eventos que updatean el juego deben implmenetar cada caso*/

class GameGUI;

class UpdateEvent {
public:
    virtual void operator()(GameGUI& game) = 0;
};


#endif //ARGENTUM_UPDATEEVENT_H
