#include "sprite.h"


GameSprite::GameSprite(){};
GameSprite::~GameSprite(){};

void GameSprite::sprite_init(const char* graphic, SDL_Renderer* ren, int frames, int duration, int start_width, int start_height){
  //get the graphic that was passed in and make a texture
  SDL_Surface* pic =IMG_Load(graphic);
  sprite_graphic = SDL_CreateTextureFromSurface(ren,pic);
  SDL_FreeSurface(pic);

  game_renderer = ren;
  frame_count = frames;
  frame_duration = duration;
  //which sprite are we looking at in the width
  frame_rect.x = 0;
  //which sprite layer to use
  frame_rect.y = 0;
  //need ot resize the square to get the individual sprite
  frame_rect.w = start_width/frame_x;
  frame_rect.h = start_height/frame_y;

}
SDL_Rect GameSprite::sprite_update(int state, int start_height){
  //this switch statement will determine what stae we are in and
  //make and connect it to the correct layer that is coorelated
  switch(state){
    case(MOVE_DOWN):
      //2nd layer down
      frame_rect.y = start_height/frame_y;
      break;
    case(MOVE_RIGHT):
      //3rd layer down
      frame_rect.y = MOVE_RIGHT*(start_height/frame_y);
      break;
    case(MOVE_LEFT):
      //4th layer down
      frame_rect.y = MOVE_LEFT*(start_height/frame_y);
      break;
    case(MOVE_UP):
      //the original layer
      frame_rect.y = 0;
      break;
    default:
      //if nothing happening just stay in idle state
      frame_rect.y = start_height/frame_y;
      break;
  }

  // will get the correct frame to be in
  int frame_time = (int)(SDL_GetTicks()/frame_duration) % frame_count;
  cout<<frame_time<<endl;

  static int last_frame_time = 0;
  //reset back to first spot if its arbitarily low
  if(frame_time<1){
    frame_rect.x = 0;
  }
  else{
    //move to the right the size of one sprite size
    frame_rect.x = frame_rect.w;
  }

  last_frame_time = frame_time;

return(frame_rect);

}
void GameSprite::sprite_render(SDL_Renderer* ren){
  // SDL_RenderCopy(ren,sprite_graphic,&frame_rect, &dst);
}
void GameSprite::sprite_quit(){
  SDL_DestroyTexture(sprite_graphic);
}
//i used a helper function to return my sprite obj_graphic
//back to the GameObject class so it could be rendered
SDL_Texture* GameSprite::get_spriteText(){
  return sprite_graphic;
}
