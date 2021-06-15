#ifndef __CPY_TO_PNG_H__
#define __CPY_TO_PNG_H__

#include <SDL2/SDL.h>

#include <string>

class Cpy2Png {
   private:
    std::string dir;
    std::string filename;

   public:
    /**
     * @brief La imagen se guardara directamente en la carpeta del ejecutable
     *
     */
    Cpy2Png();

    /**
     * @brief La imagen se guardara en dir
     *
     * @param dir Direccion donde se guardará la imagen
     */
    explicit Cpy2Png(std::string const &dir);

    /**
     * @brief Copia lo que está actualmente en el renderer a PNG.
     *
     * @param renderer De donde se copiaran los pixeles.
     */
    void copy_to_png(SDL_Renderer *renderer, int width, int height);

   private:
    void save_texture(SDL_Renderer *renderer, SDL_Texture *texture);

    void check_masks(Uint32 &rmask, Uint32 &gmask, Uint32 &bmask,
                     Uint32 &amask);
};

#endif
