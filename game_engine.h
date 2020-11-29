#ifndef game_engine_h
#define game_engine_h

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "game_object.h"
#include "particle_emitter.h"
using namespace std;

class Engine{

private:
  bool game_is_running = true;

  SDL_Window* my_window = NULL;
  SDL_Renderer* my_renderer = NULL;
  SDL_Event input;
  GameObject* player;
  ParticleEmitter* part_blow;
  SDL_Rect land_rect;


public:
  Engine();
  void init();
  void handleEvents();
  void updateMechanics();
  void render();
  void quit();
  bool getGameRunning();

};

#endif
