//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_EVENT_H
#define ARGENTUM_EVENT_H

//Interfaz para encolar eventos para game
class Event {
    virtual void operator()() = 0;
};


#endif //ARGENTUM_EVENT_H
