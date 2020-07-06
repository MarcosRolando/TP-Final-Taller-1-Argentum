#ifndef TP3TALLER_CLIENT_H
#define TP3TALLER_CLIENT_H

/*Esta clase se encarga de manejar la logica de la conexion y comuniacion
 * con el Server*/

#include "Socket.h"
#include "GameGUI.h"
#include <string>
#include "ClientEventHandler.h"

class Client {
private:
    std::string host, port;
    Socket socket;
    bool finished;

public:
    Client(std::string&& host, std::string&& port);
    Client(const Client&) = delete; /*Borro los constructores por copia*/
    Client operator=(const Client&) = delete;

    /*Levanta el cliente en el host y puerto especificados en el constructor*/
    void connect();

    ~Client();

private:
    void _processConnection();
    static void _initializeSDL();
    static void _closeSDL();
};


#endif //TP3TALLER_CLIENT_H
