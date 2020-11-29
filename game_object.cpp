#include "game_object.h"

GameObject::GameObject(){}

GameObject::~GameObject(){}

void GameObject::stationary_obj_init(const char* graphic, SDL_Renderer* ren){
  SDL_Surface* moon_pic =IMG_Load(graphic);
  moon_graph = SDL_CreateTextureFromSurface(ren,moon_pic);
  SDL_FreeSurface(moon_pic);

  moon_rect.x = 255;
  moon_rect.y = 200;
  moon_rect.w = 150;
  moon_rect.h = 150;

}


bool GameObject::collision_detection(SDL_Rect rect1 ,SDL_Rect rect2){

  float rect1L = rect1.x,
  rect1R = rect1.x+rect1.w-COLLISION_OFFSET,
  rect1UP = rect1.y,
  rect1D = rect1.y+rect1.h-COLLISION_OFFSET;


  float rect2L = rect2.x,
  rect2R = rect2.x+rect2.w-COLLISION_OFFSET,
  rect2UP = rect2.y,
  rect2D=rect2.y+rect2.h-COLLISION_OFFSET_UP;


  if(rect1R < rect2L) return false;
  if(rect1L > rect2R) return false;
  if(rect1D < rect2UP) return false;
  if(rect1UP > rect2D) return false;


  return true;
}

void GameObject::obj_init(const char* graphic, SDL_Renderer* ren){
  //initializing the player movement
  obj_rect.x = STARTING_POS_X;
  obj_rect.y = STARTING_POS_Y;
  //initializing the size of the player square
  obj_rect.w = start_width/X_FRAMES;
  obj_rect.h = start_height/Y_FRAMES;
  //making our sprite object and initializing
  obj_sprite = new GameSprite();
  obj_sprite->sprite_init(graphic,ren,X_FRAMES,100,start_width,start_height);
  //making the obj_graphic to be same as the sprites graphic
  obj_graphic = obj_sprite->get_spriteText();
}

void GameObject::obj_update(){
  //if the player goes out of bounds i want to slow them down
  if(obj_rect.x < (LEFT_BOUND - obj_rect.w/2)) x_val += 0;
  if(obj_rect.x > (RIGHT_BOUND - obj_rect.w/2)) x_val += 0;
  if(obj_rect.y > (DOWN_BOUND - obj_rect.h/2)) y_val += 0;
  if(obj_rect.y < (UP_BOUND - obj_rect.h/2)) y_val += 0;

  //if the player goes out of bounds i want to stop their movement from
  //going off screen
  if(x_pos < (LEFT_BOUND - obj_rect.w/2))  x_pos = (LEFT_BOUND-obj_rect.w/2);
  if(x_pos > (RIGHT_BOUND - obj_rect.w/2)) x_pos = (RIGHT_BOUND-obj_rect.w/2);
  if(y_pos > (DOWN_BOUND - 2*obj_rect.h))  y_pos =  (DOWN_BOUND-2*obj_rect.h);
  if(y_pos < (UP_BOUND - obj_rect.h/2))    y_pos = (UP_BOUND-obj_rect.h/2);

  //keeps the velocity from going too fast
  if(x_val<(-1*MAX_VELO)) x_val = -1*MAX_VELO;
  if(x_val>(MAX_VELO))    x_val = MAX_VELO;
  if(y_val<(-1*MAX_VELO)) y_val= -1*MAX_VELO;
  if(y_val>(MAX_VELO))    y_val = MAX_VELO;

  //update the player movement
  x_pos += x_val;
  y_pos += y_val;
  obj_rect.x = x_pos;
  obj_rect.y = y_pos;

  //determine which state we are in based off of the movement
  if(x_val == 0 && y_val ==0){
    state = IDLE;
  }
  if(x_val>0){
    state = MOVE_RIGHT;
  }
  if(x_val<0){
    state = MOVE_LEFT;
  }
  if(y_val<0){
    state = MOVE_UP;
  }
  if(y_val>0){
    state = MOVE_DOWN;
  }
  //when detect a collosion then change state
  if(collision_detection(obj_rect,moon_rect)){
    state = DEAD;
  }
  //upadate our sprite to be in the correct frame
  frame_rect = obj_sprite->sprite_update(state,start_height);

}

//render in our player movement;
//i stayed with the origianal rendercopy bc i made my own sprite and forgot
//we could flip horizontal movement
void GameObject::obj_render(SDL_Renderer* ren){
   SDL_RenderCopy(ren, obj_graphic, &frame_rect, &obj_rect);

}
//render in the moon graphic
void GameObject::moon_render(SDL_Renderer* ren){
  SDL_RenderCopy(ren, moon_graph, NULL, &moon_rect);
}

//clean up
void GameObject::obj_quit(){
  SDL_DestroyTexture(obj_graphic);
  SDL_DestroyTexture(moon_graph);
}

// these are helper functions used to get and set velocity values amongst
// other classes

int GameObject::obj_get_x_value(){
  return x_val;
}

void GameObject::obj_set_x_value(int x_vel){
  x_val = x_vel;
}

int GameObject::obj_get_y_value(){
  return y_val;
}

void GameObject::obj_set_y_value(int y_vel){
  y_val = y_vel;
}

int GameObject::obj_get_x_pos(){
  return x_pos;
}

void GameObject::obj_set_x_pos(int new_x_pos){
  x_pos = new_x_pos;
}

int GameObject::obj_get_y_pos(){
  return y_pos;
}

void GameObject::obj_set_y_pos(int new_y_pos){
  y_pos = new_y_pos;
}

int GameObject::obj_get_state(){
  return state;
}

void GameObject::obj_set_state(int new_state){
  state = new_state;
}
