#ifndef TP3TALLER_SERVERMONITOR_H
#define TP3TALLER_SERVERMONITOR_H

/*Esta clase es la que chequea cuando cerrar el server*/

#include "ArgentumServer.h"
#include "../../libs/Thread.h"

class ServerMonitor : public Thread {
private:
    ArgentumServer& server;

public:
    explicit ServerMonitor(ArgentumServer& server) : server(server) {}

private:
    /*Implementa la funcion run heredada de Thread, la cual para esta clase
    * correra el metodo stopOnCommand*/
    void run() override;

    void _stopOnCommand() const;
};


#endif //TP3TALLER_SERVERMONITOR_H
