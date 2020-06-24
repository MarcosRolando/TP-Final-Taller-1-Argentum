#ifndef TP3TALLER_TP3SERVERSIDE_H
#define TP3TALLER_TP3SERVERSIDE_H

/*Esta es la clase principal del lado del Server. Se encarga de validar los
 * datos de ejecucion del Server y, en caso de ser validos, instanciar al
 * Server. Al cerrar el Server imprime los resultados de las partidas*/

class TP3ServerSide {
public:
    static int run(int argc, char** argv);
};


#endif //TP3TALLER_TP3SERVERSIDE_H
