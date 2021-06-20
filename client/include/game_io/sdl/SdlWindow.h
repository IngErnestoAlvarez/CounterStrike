#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

#include <SDL2/SDL.h>

class SdlWindow {
   private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;

   public:
    SdlWindow();
    SdlWindow(int width, int height);

    SdlWindow &operator=(SdlWindow const &) = delete;
    SdlWindow &operator=(SdlWindow &&);

    ~SdlWindow();

    void fill(int r, int g, int b, int alpha);
    void fill();

    void render();

    void clear_renderer();

    SDL_Renderer *getRendered() const;
};

#endif
