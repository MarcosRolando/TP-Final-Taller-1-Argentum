//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_EVENT_H
#define ARGENTUM_EVENT_H

class ServerProtocol;

//Interfaz para encolar eventos para game
class Event {
public:
    virtual void operator()(ServerProtocol& protocol) = 0;
};


#endif //ARGENTUM_EVENT_H
