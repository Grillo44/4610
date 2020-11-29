#include "particle_emitter.h"

ParticleEmitter::ParticleEmitter(){}
ParticleEmitter::~ParticleEmitter(){}

void ParticleEmitter::pe_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type){

  srand(5);
  part_types = type;
  int max_parts = MAX_PARTS;

  if(part_types==PART_TYPE_BLOW){

    max_parts = MAX_PARTS_BLOW;

    for(int i = 0;i<max_parts;i++){
      //create number of particles and velocities
      particles[i].part_init(graphic,ren,start_x,start_y,width,height);
      particles[i].part_set_xvel(3.0-(rand()%60)/10.0);
      particles[i].part_set_yvel(0-(rand()%60)/10.0);
      particles[i].part_set_lifetime(20+(rand()%10));

    }
  }

}
void ParticleEmitter::pe_update(){
  int max_parts = MAX_PARTS;
  //update the particles based off particle update
  if(part_types==PART_TYPE_BLOW){
     max_parts = MAX_PARTS_BLOW;

     for(int i = 0;i<max_parts;i++){
       particles[i].part_update_blow();
     }

  }
}
void ParticleEmitter::pe_render(SDL_Renderer* ren){
  int max_parts = MAX_PARTS;

  if(part_types==PART_TYPE_BLOW){
     max_parts = MAX_PARTS_BLOW;
     //render in all the particles
     for(int i=0;i<max_parts;i++){
       particles[i].part_render_blow(ren);
     }
  }
}
void ParticleEmitter::pe_quit(){
  int max_parts = MAX_PARTS;
  //clear the particles
  if(part_types == PART_TYPE_BLOW){
    max_parts = MAX_PARTS_BLOW;
    for(int i = 0;i<max_parts;i++){
      particles[i].part_quit();
    }
  }
}
