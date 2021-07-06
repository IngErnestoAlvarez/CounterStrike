#ifndef __PROTOCOLO_H__
#define __PROTOCOLO_H__

#include <string>

#include "socket.h"

class Game;

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
    CW1 = 0x63,
    CW2 = 0x65,
    CW3 = 0x66,
    // Change to bomb
    CB = 0x67,
    BW = 0x62,
    USE = 0x79,
    STOP = 0x7A
};

class Protocolo {
   private:
    Game *game;

   public:
    // cliente
    Protocolo();

    // servidor
    Protocolo(Game *game);

    ~Protocolo();

    /**
     * ! Mouse:
     *
     *   - Dos bytes. 1° x, 2° y
     */

    void send_one_byte(socket_t *skt, uint8_t *byte);

    void send_two_bytes(socket_t *skt, uint16_t *bytes);

    void send_four_bytes(socket_t *skt, uint32_t *bytes);

    uint8_t receive_one_byte(socket_t *skt);

    uint16_t receive_two_bytes(socket_t *skt);

    uint32_t receive_four_bytes(socket_t *skt);

    // SERVIDOR
    // 45, 100
    // angulodestencil (2bytes), radiodestencil(2bytes)
    // 2bytes con cant de bodies (1 tipo, 2posx, 2posy)
    void send_config(socket_t *skt);

    // CLIENTE
    void recv_config(socket_t *skt);

    // SERVIDOR
    // 2bytes con cant de bodies (1 tipo, 2 posx, 2 posy, 4 angle)
    void send_state(socket_t *skt);

    // CLIENTE
    void recv_state(char **result, size_t *size, socket_t *skt);

    // CLIENTE
    void send_comando(Comando comando, socket_t *skt);

    void recv_comando(Comando *comando, socket_t *skt);
    // CLIENTE
    // (2 x, 2 y)
    void send_mouse(int x, int y, socket_t *skt);

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
    // void send_player(Player &player);

    void recv_player(char **result, size_t *size, socket_t *skt);

   private:
};

#endif  // __PROTOCOLO_H__
