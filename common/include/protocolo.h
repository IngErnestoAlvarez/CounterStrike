#ifndef __PROTOCOLO_H__
#define __PROTOCOLO_H__

#include "socket.h"

/**
 * ! Comandos (HEX):
 **  - MoveUp "75"
 **  - MoveDown "64"
 **  - MoveLeft "6C"
 **  - MoveRight "72"
 **  - Shoot "73"
 **  - ChangeWeapon "63" (x4)
 **  - BuyWeapon "62" ("armaID")
 **  - Use "79"
 **  - Stop "7A"
 */

#define COMMAND_SIZE 1
enum Comando : unsigned char {
    UP = 0x75,
    DOWN = 0x64,
    LEFT = 0x6C,
    RIGHT = 0x72,
    SHOOT = 0x73,
    CW = 0x63,
    BW = 0x62,
    USE = 0x79,
    STOP = 0x7A
};

class Protocolo {
   private:
    socket_t *skt;

   public:
    Protocolo(socket_t *skt);
    ~Protocolo();

    /**
     * ! Mouse:
     *
     *   - Dos bytes. 1° x, 2° y
     */

    // SERVIDOR
    void send_config();

    // CLIENTE
    void recv_config();

    // SERVIDOR
    void send_state();

    // CLIENTE
    void recv_state();

    // CLIENTE
    void send_comando(Comando comando);

    void recv_comando(Comando *comando);
    // CLIENTE
    void send_mouse(int x, int y);

   private:
};

#endif  // __PROTOCOLO_H__
