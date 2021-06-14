#ifndef __STENCIL_H__
#define __STENCIL_H__

#include <SDL2/SDL.h>

class Stencil {
   private:
    int cone_angle;
    int circle_radius;

   public:
    Stencil();

    Stencil(int cone_angle, int circle_radius);

    ~Stencil();

    void make_stencil(SDL_Renderer *renderer);

   private:
    void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b,
                   Uint8 a);

    void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius,
                     Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r,
                     Uint8 g, Uint8 b, Uint8 a);

    void draw_vision_cone();
};

#endif
