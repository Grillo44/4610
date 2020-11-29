#ifndef particles_h
#define particles_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
using namespace std;

#define MAX_PARTS 20
#define MAX_PARTS_BLOW 15

#define PART_TYPE_BLOW 1

class Particle{

  private:
    SDL_Texture* part_graphic;
    SDL_Rect part_rect;

    float xpos;
    float ypos;
    float xvel;
    float yvel;

    int width;
    int height;

    int state;
    int lifetime;

    SDL_Renderer* part_renderer;

  public:
    Particle();
    ~Particle();

    void part_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height);
    void part_update_blow();
    void part_render_blow(SDL_Renderer* ren);
    void part_quit();
    int  part_get_xvel();
    void part_set_xvel(float new_xvel);
    int  part_get_yvel();
    void part_set_yvel(float new_yvel);
    int  part_get_xpos();
    void part_set_xpos(float new_xpos);
    int  part_get_ypos();
    void part_set_ypos(float new_ypos);
    int  part_get_lifetime();
    void part_set_lifetime(int new_lt);
    int  part_get_state();
    void part_set_state(int new_state);


};

#endif
