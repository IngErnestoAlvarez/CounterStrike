#ifndef __MODELOIO_H__
#define __MODELOIO_H__

#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/initializer.h"
#include "game_logic/modelo_logic.h"

class ModeloIO {
   private:
    Initializer init;
    SdlWindow window;
    ModeloLogic *modelo;
    bool active;
    SdlObject player_view;

   public:
    ModeloIO();
    ModeloIO(ModeloLogic &logica);

    ~ModeloIO();

    /**
     * @brief Actualizacion del modelo IO.
     *
     * @return false si se cerró la ventana.
     */
    bool update();

    SdlWindow &getWindow();

   private:
    void check_actions();
    void check_events();
    void check_keyboard();
    void check_mouse();

    void clearRenderer();

    void render();
};

#endif  // __MODELOIO_H__
