#ifndef TP3TALLER_SOCKET_H
#define TP3TALLER_SOCKET_H

#include <cstdio>
#include <string>

class Socket {
private:
    int fd; /*File Descriptor*/

public:
    Socket();
    Socket(const Socket&) = delete; /*Borro los constructores por copia*/
    Socket operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) noexcept;
    Socket(Socket&& srcSocket) noexcept;

    /*Conecta el cliente al servidor*/
    void connect(std::string& host, std::string& port);

    /*Acepta una nueva conexion, retornando el socket generado*/
    Socket accept() const;

    /*Bindea a un socket*/
    void bind(std::string& port);

    /*Setea la cantidad maxima de clientes que se tendran en espera*/
    void maxListen(int max) const;

    /*Envia el mensaje*/
    void send(const char* message, size_t length) const;

    /*Recibe el mensaje*/
    void receive(char* message, size_t length) const;

    /*Cierra el socket*/
    void close();

    ~Socket();

private:
    explicit Socket(int fd) : fd(fd) {}
    static struct addrinfo* _getAddresses(std::string* host, std::string* port);
};


#endif //TP3TALLER_SOCKET_H
