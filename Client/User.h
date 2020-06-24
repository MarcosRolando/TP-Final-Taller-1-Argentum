#ifndef TP3TALLER_USER_H
#define TP3TALLER_USER_H

/*Esta clase se encarga de manejar las interacciones con el usuario por
 * stdin*/

#include <string>

class User {
public:
    /*Retorna el input del usuario*/
    static std::string getInput();

    /*Le muestra un mensaje al usuario*/
    static void showMessage(const char* message);
};

#endif //TP3TALLER_USER_H
