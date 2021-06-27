#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdlib.h>

struct socket_t {
   private:
    int fd;

   public:
    class SocketClosed : public std::exception {
       private:
        std::string message;

       public:
        SocketClosed(std::string const &error);

        const char *what() const noexcept;
    };
    // Incializa una instancia para ser utilizada.
    // Post: Devuelve 1 si hubo un error, 0 si no.
    socket_t();

    socket_t(const socket_t &) = delete;

    socket_t(socket_t &&) noexcept;

    socket_t &operator=(socket_t const &) = delete;
    socket_t &operator=(socket_t &&other) noexcept;
    // Destruye la instancia.
    ~socket_t();

    // Vincula el socket al puerto host con el tipo
    // servicio.
    // Solo para servidores.
    // Post: Devuelve 1 si hubo un error, 0 si no.
    int bind_and_listen(const char *host, const char *servicio,
                        size_t tam_queue);

    // Acepta un socket a traves de self y lo almacena en aceptado.
    // Solo para servidores. Si aceptado tenia un socket valido,
    // esta función lo reemplaza por uno nuevo (es cerrado correctamente).
    // Pre: self fue previamente vinculado via
    // bind_and_listen().
    // Post: Devuelve 2 si se cerró el skt, devuelve 1 si hubo un error, 0 si
    // no.
    int accept(socket_t *aceptado);

    // Conecta el socket al host con el tipo servicio.
    // Solo para clientes.
    // Post: Devuelve 1 si hubo un error, 0 si no.
    int connect(const char *host, const char *servicio);

    // Envia el mensaje a traves del socket.
    // Post: Devuelve 1 si hubo un error, 0 si no.
    int send(char const *buffer, size_t n);

    /**
     * @brief Recibe el mensaje a traves del socket, devuelve a traves de
     * received la cantidad de bytes leidos.
     * @throws SocketClosed Si el socket se cerró.
     * @throws std::runtime_exception Si hubo un error con el socket.
     */
    void receive(char *buffer, size_t n, size_t &received);

    void shutdown();

   private:
    int socket_servidor(const char *nombre_host, const char *servicio);

    int socket_addrinfo(const char *nombre_host, const char *servicio,
                        struct addrinfo **resultado);
};
#endif
