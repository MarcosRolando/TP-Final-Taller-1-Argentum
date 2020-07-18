//
// Created by agustin on 23/6/20.
//

#ifndef ARGENTUM_EVENT_H
#define ARGENTUM_EVENT_H

class ServerProtocol;

//Interfaz para encolar eventos para game
class Event {
public:

    //Funcion a implementar para cada clase que herede de esta, debe realizar
    //la accion del juegoq que se quiere ejecutar
    virtual void operator()(ServerProtocol& protocol) = 0;
    virtual ~Event() = default;
};


#endif //ARGENTUM_EVENT_H
