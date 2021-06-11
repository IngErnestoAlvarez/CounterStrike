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
    SdlWindow(int width, int height);

    ~SdlWindow();

    void fill(int r, int g, int b, int alpha);
    void fill();

    void render();

    SDL_Renderer *getRendered() const;
};

#endif
