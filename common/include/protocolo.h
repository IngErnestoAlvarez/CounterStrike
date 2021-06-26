

class Protocolo {
   public:
    Protocolo();
    ~Protocolo();

    /**
     * ! Comandos:
     **  - MoveUp "75"
     **  - MoveDown "64"
     **  - MoveLeft "6C"
     **  - MoveRight "72"
     **  - Shoot "73"
     **  - ChangeWeapon "63" (x4)
     **  - BuyWeapon "62" ("armaID")
     **  - Use "79"
     **  - Stop "7A"
     *
     * ! Mouse:
     *
     *   - Dos bytes. 1° x, 2° y
     */

    // SERVIDOR
    send_config();

    // CLIENTE
    recv_config();

    // SERVIDOR
    send_state();

    // CLIENTE
    recv_state();

    // CLIENTE
    send_comando(Comando comando);

    // CLIENTE
    send_mouse(int x, int y);

   private:
};
