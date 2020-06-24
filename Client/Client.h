#ifndef TP3TALLER_CLIENT_H
#define TP3TALLER_CLIENT_H

/*Esta clase se encarga de manejar la logica de la conexion y comuniacion
 * con el Server*/

#include "Socket.h"
#include "client_ClientProtocol.h"
#include <string>

class Client {
private:
    std::string host, port;
    Socket socket;
    ClientProtocol protocol;
    bool finished;

public:
    Client(std::string&& host, std::string&& port) : host(host), port(port),
                                                            finished(false) {}
    Client(const Client&) = delete; /*Borro los constructores por copia*/
    Client operator=(const Client&) = delete;

    /*Levanta el cliente en el host y puerto especificados en el constructor*/
    void connect();

private:
    void _send() const;
    void _receive();
    void _processConnection();
};


#endif //TP3TALLER_CLIENT_H
