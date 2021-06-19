#ifndef __MODELOIO_H__
#define __MODELOIO_H__

#include "game_io/sdl/SdlWindow.h"
#include "game_logic/modelo_logic.h"

class ModeloIO {
   private:
    SdlWindow window;
    ModeloLogic *modelo;
    bool active;

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
};

#endif  // __MODELOIO_H__
