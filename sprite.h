#ifndef sprite_h
#define sprite_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
using namespace std;
//these are used to switch states to get the correct sprite layer
#define IDLE 1
#define MOVE_DOWN 1
#define MOVE_RIGHT 2
#define MOVE_LEFT 3
#define MOVE_UP 0
//number of frames in width and height
#define X_FRAMES 3
#define Y_FRAMES 4


using namespace std;

class GameSprite{

private:
  SDL_Texture* sprite_graphic;
  SDL_Rect frame_rect;


  int frame_x = X_FRAMES;
  int frame_y = Y_FRAMES;

  int frame_count;
  int frame_duration;
  SDL_Renderer* game_renderer;

public:
  GameSprite();
  ~GameSprite();
  SDL_Texture* get_spriteText();
  void sprite_init(const char* graphic, SDL_Renderer* ren, int frames, int frame_duration, int start_width, int start_height);
  SDL_Rect sprite_update(int state, int start_height);
  void sprite_render(SDL_Renderer* ren);
  void sprite_quit();
};

#endif
