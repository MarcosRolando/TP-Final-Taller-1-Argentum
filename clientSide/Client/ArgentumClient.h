#ifndef TP3TALLER_CLIENT_H
#define TP3TALLER_CLIENT_H

/*Esta clase se encarga de manejar la logica de la conexion y comuniacion
 * con el Server*/

#include "../../libs/Socket.h"
#include "GameGUI.h"
#include <string>
#include "ClientEventHandler.h"

struct GameStartInfo;

class Client {
private:
    Socket socket;

public:
    /* Constructor */
    Client();
    Client(const Client&) = delete; /*Borro los constructores por copia*/
    Client operator=(const Client&) = delete;

    /* Comienza la ejecucion del cliente */
    void run();
    /* Destructor */
    ~Client();

private:
    void _gameLoop();
    static void _initializeSDL();
    static void _closeSDL();
    static void _setCursor();
};


#endif //TP3TALLER_CLIENT_H
