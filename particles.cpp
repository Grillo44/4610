#include "particles.h"

Particle::Particle(){}
Particle::~Particle(){}

void Particle::part_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height){
  //laod in explosion picture
  SDL_Surface* pic =IMG_Load(graphic);
  part_graphic = SDL_CreateTextureFromSurface(ren,pic);
  SDL_FreeSurface(pic);
  //set positioning for explosion
  xpos = start_x;
  ypos = start_y;
  part_renderer = ren;
  part_rect.x = xpos;
  part_rect.y = ypos;
  part_rect.h = height;
  part_rect.w = width;

  xvel = 0;
  yvel = 0;


}
void Particle::part_update_blow(){
  xpos += xvel;
  ypos += yvel;
  //during lifetime
  if(lifetime>0){
    //change how it moves
    part_rect.x = (int)xpos;
    part_rect.y = (int)ypos;
    //change the sizing
    part_rect.w = (int)width/2 + width*(int)(10*lifetime/100);
    part_rect.h = (int)height/2 + height*(int)(10*lifetime/100);

  }
  lifetime-=1;
}

void Particle::part_render_blow(SDL_Renderer* ren){
  //render during lifetime
  if(lifetime>0){

    SDL_RenderCopy(ren,part_graphic,NULL,&part_rect);

  }
}
void Particle::part_quit(){
  SDL_DestroyTexture(part_graphic);
}
int  Particle::part_get_xvel(){
  return (int)xvel;
}
void Particle::part_set_xvel(float new_xvel){
  xvel = new_xvel;
}
int  Particle::part_get_yvel(){
  return (int)yvel;
}
void Particle::part_set_yvel(float new_yvel){
  yvel = new_yvel;
}
int  Particle::part_get_xpos(){
  return (int)xpos;
}
void Particle::part_set_xpos(float new_xpos){
  xpos = new_xpos;
}
int  Particle::part_get_ypos(){
  return (int)ypos;
}
void Particle::part_set_ypos(float new_ypos){
  ypos = new_ypos;
}
int  Particle::part_get_lifetime(){
  return lifetime;
}
void Particle::part_set_lifetime(int new_lt){
  lifetime = new_lt;
}
int  Particle::part_get_state(){
  return state;
}
void Particle::part_set_state(int new_state){
  state = new_state;
}
