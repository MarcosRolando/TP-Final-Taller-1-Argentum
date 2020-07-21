//
// Created by marcos on 13/7/20.
//

#ifndef ARGENTUM_UPDATEMANAGER_H
#define ARGENTUM_UPDATEMANAGER_H

#include "Update.h"
#include "../UpdateEvents/UpdateEvent.h"
#include <mutex>
#include <memory>

/*Almacena los udpates que recibe del server, los cuales serian consumidos
 * por el thread principal en el main game loop*/

class UpdateManager {
private:
    std::mutex m;
    std::queue<Update> updates;

public:
    /*Agrega un update*/
    void push(Update& update);

    /*Retorna el siguiente update, eliminandolo de la cola de updates*/
    Update pop();

    /*Retorna la cantidad de updates disponibles (cantidad en la cola)*/
    int updatesAvailable();
};


#endif //ARGENTUM_UPDATEMANAGER_H
