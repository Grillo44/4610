#ifndef particle_emitter_h
#define particle_emitter_h

#include "particles.h"
class ParticleEmitter{

  private:
    Particle particles[MAX_PARTS];
    int xpos;
    int ypos;
    int part_types;

  public:
    ParticleEmitter();
    ~ParticleEmitter();

    void pe_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type);
    void pe_update();
    void pe_render(SDL_Renderer* ren);
    void pe_quit();

};

#endif
