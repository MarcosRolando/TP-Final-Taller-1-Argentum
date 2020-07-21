#ifndef TP3TALLER_SERVERMONITOR_H
#define TP3TALLER_SERVERMONITOR_H

/*Esta clase es la que chequea cuando cerrar el server*/

#include "ArgentumServer.h"
#include "../../libs/Thread.h"

class ServerMonitor : public Thread {
private:
    ArgentumServer& server;
    bool reading{true};

public:
    explicit ServerMonitor(ArgentumServer& server) : server(server) {}
    void join() override;

    /*Retorna true si se cerro el servidor a pedido del usuario,
     * false en caso contrario*/
    bool closeRequest();

private:
    /*Implementa la funcion run heredada de Thread, la cual para esta clase
    * correra el metodo stopOnCommand*/
    void run() override;
    void _stopOnCommand();
};


#endif //TP3TALLER_SERVERMONITOR_H
