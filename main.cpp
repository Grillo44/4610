#include "game_engine.h"

int main(){

  const int fps = 60;
  const int frame_duration = 1001 / fps;
  Uint32 this_start_time = 0;
  Uint32 last_count_time = 0;
  Uint32 this_duration = 0;
  int fps_counter = 0, current_fps = 0;

  Engine* ge  = new Engine();
  ge->init();
  while (ge->getGameRunning()) {
	  this_start_time = SDL_GetTicks();

	  ge->handleEvents();
    ge->updateMechanics();
    ge->render();

    fps_counter++;
    if (this_start_time >= (last_count_time + 1000)) {
      last_count_time = this_start_time;
      current_fps = fps_counter;
      fps_counter = 0;
    }
    cout << current_fps << endl;
    this_duration = SDL_GetTicks() - this_start_time;

    if (this_duration < frame_duration) {
      SDL_Delay(frame_duration - this_duration);
    }
  }

  ge->quit();
return 0;
}
