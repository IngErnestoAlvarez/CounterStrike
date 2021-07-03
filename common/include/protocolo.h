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

/**
 * ! Comandos (HEX):
 *  - SePlantoBomba
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
    // 45, 100
    // angulodestencil (2bytes), radiodestencil(2bytes)
    // 2bytes con cant de bodies (1 tipo, 2posx, 2posy)
    void send_config();

    // CLIENTE
    void recv_config();

    // SERVIDOR
    // 2bytes con cant de bodies (1 tipo, 2 posx, 2 posy, 4 angle)
    void send_state();

    // CLIENTE
    void recv_state();

    // CLIENTE
    void send_comando(Comando comando);

    void recv_comando(Comando *comando);
    // CLIENTE
    // (2 x, 2 y)
    void send_mouse(int x, int y);

    /**
     * ammo 1byte
     * life 1byte
     * dinero 2bytes
     * posx 2 bytes
     * posy 2 bytes
     * angle 4 bytes
     * actualweapon 1byte
     * tiempo 1byte
     * gotbomb 1byte
     *
     * @param player
     */
    void send_player(Player &player);

    void recv_player();

   private:
};

#endif  // __PROTOCOLO_H__
