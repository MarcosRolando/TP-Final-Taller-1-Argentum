#ifndef TP3TALLER_THREAD_H
#define TP3TALLER_THREAD_H

/*Esta clase es abstracta, las clases que heredan de ella pueden correr el
 * metodo run en un thread nuevo*/

#include <thread>

class Thread {
private:
    std::thread thread;

public:
    /*Ejecuta en un nuevo thread al metodo run*/
    void operator()();

    /*Joinea el thread*/
    virtual void join();

    /*Libera el thread violentamente*/
    void detach();

    virtual ~Thread() = default;

protected:
    /*Metodo abstracto, las clases hijas deben implementarlo*/
    virtual void run() = 0;
};


#endif //TP3TALLER_THREAD_H
