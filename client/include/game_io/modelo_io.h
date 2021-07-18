#ifndef __MODELOIO_H__
#define __MODELOIO_H__

#include <vector>

#include "game_io/pauser.h"
#include "game_io/renderizables.h"
#include "game_io/rounds.h"
#include "game_io/sdl/SdlObject.h"
#include "game_io/sdl/SdlWindow.h"
#include "game_io/sdl/initializer.h"
#include "game_io/sdl/text/SdlText.h"
#include "game_io/shopping.h"
#include "game_io/sound/music.h"
#include "game_proxy/body_proxy.h"
#include "game_proxy/modelo_proxy.h"
#include "types.h"

class ModeloIO {
   private:
    Initializer init;
    SdlWindow window;
    ModeloProxy &modelo;
    bool active;
    Renderizables renderizables;
    Music music;
    Shopping shop;
    RoundScore score;
    Pauser pauser;

   public:
    /**
     * @brief Construccion del ModeloIO, es estrictamente necesario la creacion
    de un
     * ModeloProxy conectado a un servidor adecuado para poder funcionar
    correctamente.
     *
     * @param logica ModeloProxy conectado a un servidor.
     */
    ModeloIO(ModeloProxy &logica);

    ~ModeloIO();

    /**
     * @brief Actualizacion del modelo IO.
     *
     * @return false si se cerró la ventana.
     */
    bool update();

    SdlWindow &getWindow();

    void check_actions();

   private:
    void check_events();
    void check_keyboard();
    void check_mouse();

    void clearRenderer();

    void renderPhase(Phase phase);

    void renderWaiting();
    void renderPreparing();
    void renderPlaying();
};

#endif  // __MODELOIO_H__
