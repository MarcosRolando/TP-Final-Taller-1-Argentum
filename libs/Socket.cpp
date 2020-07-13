#include "Socket.h"
#include <netdb.h>
#include <unistd.h>
#include "TPException.h"
#include <cstring>

#define CONNECT_ERROR_MSG "Could not connect. "
#define BIND_ERROR_MSG "Could not bind. "
#define ACCEPT_ERROR_MSG "Error in accept: "
#define SEND_ERROR_MSG "Error in send: "
#define RECV_ERROR_MSG "Error in recv: "
#define GETADDRINFO_ERROR_MSG "Error in getaddrinfo: %s"

struct addrinfo* Socket::_getAddresses(std::string* host, const std::string* port) {
    struct addrinfo hints{}, *result;
    int s; /*Para verificar errores*/
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (host) {
        hints.ai_flags = 0; /*cliente*/
        s = getaddrinfo(host->c_str(), port->c_str(), &hints, &result);
    } else {
        hints.ai_flags = AI_PASSIVE; /*server*/
        s = getaddrinfo(nullptr, port->c_str(), &hints, &result);
    }
    if (s != 0) throw TPException(GETADDRINFO_ERROR_MSG, gai_strerror(s));
    return result;
}

void Socket::connect(std::string& host, std::string& port) {
    struct addrinfo* addresses = _getAddresses(&host, &port);
    struct addrinfo* rp;
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd  == -1)
            continue;

        if (::connect(fd , rp->ai_addr, rp->ai_addrlen) != -1)
            break; /*Logre conectarme*/

        ::close(fd);
    }
    freeaddrinfo(addresses);
    if (rp == nullptr) {
        throw TPException(CONNECT_ERROR_MSG);
    }
}

void Socket::bind(const std::string& port) {
    struct addrinfo* addresses = _getAddresses(nullptr, &port);
    struct addrinfo* rp;
    int val = 1;
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd == -1)
            continue;

        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (::bind(fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /*Logre bindear*/

        ::close(fd);
    }
    freeaddrinfo(addresses);
    if (rp == nullptr) {
        throw TPException(BIND_ERROR_MSG);
    }
}

Socket Socket::accept() const {
    int peerFd = ::accept(fd, nullptr, nullptr);
    if (peerFd == -1) {
        throw TPException(ACCEPT_ERROR_MSG);
    }
    return Socket(peerFd);
}

void Socket::send(const char* message, size_t length) const {
    size_t bytesSent = 0;
    int s = 0;

    while (bytesSent < length) {
        s = ::send(fd, message + bytesSent, length - bytesSent, MSG_NOSIGNAL);
        if (s < 1) throw TPException(SEND_ERROR_MSG);
        bytesSent += s;
    }
}

void Socket::receive(char* message, size_t length) const {
    size_t bytesReceived = 0;
    int s = 0;

    while (bytesReceived < length) {
        s = recv(fd, message + bytesReceived, length - bytesReceived, 0);
        if (s < 1) throw TPException(RECV_ERROR_MSG);
        bytesReceived += s;
    }
}

void Socket::maxListen(int max) const {
    listen(fd, max);
}

Socket::~Socket() {
    close();
}

Socket::Socket(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1;
}

Socket& Socket::operator=(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1;
    return *this;
}

void Socket::close() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        ::close(fd);
        fd = -1;
    }
}

Socket::Socket() {
    fd = -1;
}
