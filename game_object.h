#ifndef game_object_h
#define game_object_h

#include "sprite.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
using namespace std;
//define the size of our game screen
//these are also used in GameEngine class
#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 680

#define STARTING_POS_X 20
#define STARTING_POS_Y 20
// these are the boundries that are set to limit character movement
#define LEFT_BOUND 0
#define RIGHT_BOUND SCREEN_WIDTH
#define UP_BOUND 0
#define DOWN_BOUND SCREEN_HEIGHT
#define MAX_VELO 8
//these are to determine what stae of movement we are in
#define IDLE 1
#define MOVE_DOWN 1
#define MOVE_RIGHT 2
#define MOVE_LEFT 3
#define MOVE_UP 0
#define DEAD 4
//number of frames for the sprite's width and height
#define X_FRAMES 3
#define Y_FRAMES 4
//made collosion offsets to get more precise
//point of contact
#define COLLISION_OFFSET 70
#define COLLISION_OFFSET_UP 60


class GameObject{
private:
  //these are to determine player speed in x & y direction
  int x_val = 0;
  int y_val = 0;
  int x_pos = STARTING_POS_X;
  int y_pos = STARTING_POS_Y;
  SDL_Renderer* obj_renderer;
  SDL_Texture* obj_graphic;
  SDL_Texture* moon_graph;
  SDL_Rect obj_rect;
  SDL_Rect frame_rect;
  SDL_Rect moon_rect;
  //state variable used in switch statment
  int state;
  GameSprite* obj_sprite;


  //this was the size of the origianl sprite png file
  int start_height = 692;
  int start_width  = 720;

public:
  GameObject();
  ~GameObject();
  void stationary_obj_init(const char* graphic, SDL_Renderer* ren);
  void obj_init(const char* graphic, SDL_Renderer* ren);
  bool collision_detection(SDL_Rect,SDL_Rect);
  void obj_update();
  void obj_render(SDL_Renderer* ren);
  void moon_render(SDL_Renderer* ren);

  void obj_quit();
  int obj_get_x_value();
  void obj_set_x_value(int x_vel);
  int obj_get_y_value();
  void obj_set_y_value(int y_vel);
  int obj_get_x_pos();
  void obj_set_x_pos(int new_x_pos);
  int obj_get_y_pos();
  void obj_set_y_pos(int new_y_pos);
  int obj_get_state();
  void obj_set_state(int new_state);
};

#endif
