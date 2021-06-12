#include "stencil.h"

Stencil::Stencil(int cone_angle, int circle_radius)
    : cone_angle(cone_angle), circle_radius(circle_radius) {}

Stencil::Stencil() : Stencil(90, 150) {}

Stencil::~Stencil() {}

void Stencil::make_stencil(SDL_Renderer *renderer) {
    this->draw_circle(renderer, 100, 100, 30, 255, 255, 255, 255);
    this->fill_circle(renderer, 100, 100, 30, 255, 255, 255, 255);
    this->draw_vision_cone();
}

void Stencil::draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius,
                          Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    double error = (double)-radius;
    double x = (double)radius - 0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y) {
        this->set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
        this->set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

        if (x != 0) {
            this->set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
            this->set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
        }

        if (y != 0) {
            this->set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
            this->set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
        }

        if (x != 0 && y != 0) {
            this->set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
            this->set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0) {
            --x;
            error -= x;
            error -= x;
        }
    }
}

void Stencil::fill_circle(SDL_Renderer *surface, int cx, int cy, int radius,
                          Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    for (double dy = 1; dy <= radius; dy += 1.0) {
        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
        SDL_SetRenderDrawColor(surface, r, g, b, a);
        SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx,
                           cy + dy - radius);
        SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx,
                           cy - dy + radius);
    }
}

void Stencil::set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g,
                        Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    SDL_RenderDrawPoint(rend, x, y);
}

void Stencil::draw_vision_cone() {}
