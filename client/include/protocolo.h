#ifndef __PROTOCOLO_H__
#define __PROTOCOLO_H__

#include <string>

#include "game_proxy/final_scores.h"
#include "socket.h"
#include "types.h"

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
    NO_COMMAND = 0x00,
    UP = 0x75,
    DOWN = 0x64,
    LEFT = 0x6C,
    RIGHT = 0x72,
    SHOOT = 0x73,
    CW1 = 0x63,  // AK47
    CW2 = 0x65,  // AWP
    CW3 = 0x66,  // M3
    // Change to bomb
    CB = 0x67,  // Balas
    BW = 0x62,
    USE = 0x79,  // desactivar bomba
    STOP = 0x7A,
    AIM = 0x41,
};

class Protocolo {
   private:
   public:
    // cliente
    Protocolo();

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

    // CLIENTE
    /**
     * @brief Crea un array dinamico en result, obligacion del usuario
     * eliminarlo.
     *
     * @param result Donde se guardara el resultado
     * @param size tamaño del resultado
     * @param skt socket por el que se quiere recibir la informacion.
     * Tiene que estar conectado a un servidor
     */
    void recv_config(char **result, size_t *size, socket_t *skt);

    // CLIENTE
    void recv_state(char **result, size_t *size, uint8_t *roundResult,
                    Phase *gamePhase, uint8_t *teamAMoney, uint8_t *teamBMoney,
                    socket_t *skt);

    // CLIENTE
    void send_comando(Comando comando, socket_t *skt);

    // CLIENTE
    // (2 x, 2 y)
    void send_mouse(int x, int y, socket_t *skt);

    void send_angle(float angle, socket_t *skt);

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

    // team_id 1byte (1 = team_a, 2 = team_b)
    void send_login(socket_t *skt, TeamID team_id);

    void recv_final(FinalScores &fScores, socket_t *skt);

   private:
};

#endif  // __PROTOCOLO_H__
