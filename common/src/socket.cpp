#include "socket.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

// Sockets
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdexcept>
#include <system_error>

socket_t::socket_t() { this->fd = -1; }

socket_t::~socket_t() {
    try {
        if (this->fd >= 0) {
            this->shutdown();
        }
    } catch (...) {
        std::cout << "Error con el shutdown final del socket";
    }

    if (this->fd >= 0) close(this->fd);
}

int socket_t::bind_and_listen(const char *host, const char *servicio,
                              size_t tam_queue) {
    if (this->fd == -1) {
        if (socket_servidor(host, servicio)) {
            this->fd = -1;
            return 1;
        }
    }
    int status = listen(this->fd, tam_queue);

    if (status == -1) {
        close(this->fd);
        this->fd = -1;
        return 1;
    }

    return 0;
}

int socket_t::accept(socket_t *aceptado) {
    int sktaux = ::accept(this->fd, 0, 0);
    if (sktaux == -1) {
        if (errno == EINVAL) return 2;
        fprintf(stderr, "Error accept: %s\n", strerror(errno));
        return 1;
    }

    if (aceptado->fd >= 0) {
        ::shutdown(aceptado->fd, SHUT_RDWR);
        close(aceptado->fd);
    }
    aceptado->fd = sktaux;
    return 0;
}

int socket_t::connect(const char *host, const char *servicio) {
    struct addrinfo *ptr, *info;
    if (socket_addrinfo(host, servicio, &info)) return 1;
    bool estamos_conectados = false;
    int status;
    int skt = 0;

    for (ptr = info; ptr != NULL && estamos_conectados == false;
         ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            freeaddrinfo(info);
            return 1;
        } else {
            status = ::connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (status == -1) {
                close(skt);
            }
            estamos_conectados = (status == 0);
        }
    }
    if (!estamos_conectados) {
        fprintf(stderr, "Error al intentar conectarse al skt");
        close(skt);
        freeaddrinfo(info);
        return 1;
    }
    this->fd = skt;
    freeaddrinfo(info);
    return 0;
}

int socket_t::send(char const *buffer, size_t n) {
    size_t bytes_enviados = 0;

    while (n > bytes_enviados) {
        int estado = ::send(this->fd, &(buffer[bytes_enviados]),
                            n - bytes_enviados, MSG_NOSIGNAL);
        if (estado == -1) {
            fprintf(stderr, "Error con el skt: %s\n", strerror(errno));
            return 1;
        } else {
            bytes_enviados += estado;
        }
    }
    return 0;
}

int socket_t::receive(char *buffer, size_t n, size_t &received) {
    received = 0;

    while (received < n) {
        int estado = ::recv(this->fd, &(buffer[received]), n - received, 0);
        if (estado == 0) {
            return 1;
        } else if (estado == -1) {
            fprintf(stderr, "Error al recibir: %s\n", strerror(errno));
            return -1;
        } else {
            received += estado;
        }
    }
    return 0;
}

int socket_t::socket_servidor(const char *nombre_host, const char *servicio) {
    struct addrinfo *ptr, *info;

    if (socket_addrinfo(nombre_host, servicio, &info)) {
        return 1;
    }
    bool estamos_conectados = false;
    int skt = 0;
    int val = 1, status;

    for (ptr = info; ptr != NULL && estamos_conectados == false;
         ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt == -1) {
            fprintf(stderr, "Error al iniciar socket para servidor: %s\n",
                    strerror(errno));
            freeaddrinfo(info);
            return 1;
        } else {
            status =
                setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
            if (status == -1) {
                close(skt);
                freeaddrinfo(info);
                return 1;
            }

            status = bind(skt, info->ai_addr, info->ai_addrlen);
            if (status == -1) {
                freeaddrinfo(info);
                close(skt);
                return 1;
            }
            estamos_conectados = (status == 0);
        }
    }
    if (!estamos_conectados) {
        fprintf(stderr, "Error al intentar conectarse al skt");
        close(skt);
        freeaddrinfo(info);
        return 1;
    }
    this->fd = skt;
    freeaddrinfo(info);
    return 0;
}

int socket_t::socket_addrinfo(const char *nombre_host, const char *servicio,
                              struct addrinfo **resultado) {
    struct addrinfo hints;
    int status;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (!nombre_host) {
        hints.ai_flags = 0;
    } else {
        hints.ai_flags = AI_PASSIVE;
    }

    if (!nombre_host) {
        status = getaddrinfo(0, servicio, &hints, resultado);
    } else {
        status = getaddrinfo(nombre_host, servicio, &hints, resultado);
    }
    if (status != 0) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return 1;
    }
    return 0;
}

void socket_t::shutdown() {
    if (::shutdown(this->fd, SHUT_RD) == -1) {
        if (errno != ENOTCONN)
            throw std::system_error(ENOTCONN, std::system_category(),
                                    strerror(errno));
    }
    if (::shutdown(this->fd, SHUT_WR)) {
        if (errno != ENOTCONN)
            throw std::system_error(ENOTCONN, std::system_category(),
                                    strerror(errno));
    }
}

socket_t::socket_t(socket_t &&other) noexcept {
    this->fd = other.fd;
    other.fd = -1;
}

socket_t &socket_t::operator=(socket_t &&other) noexcept {
    if (this == &other) return *this;

    this->fd = other.fd;
    other.fd = -1;

    return *this;
}
