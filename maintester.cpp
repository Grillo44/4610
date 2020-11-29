// CS 4160 - starter code written by Victor Zordan

#include <iostream>
#include <string>
//#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
using namespace std;

const int fps = 60;
const int frame_duration = 1001 / fps;

//Screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* my_window = NULL;
SDL_Renderer* my_renderer = NULL;
SDL_Event input;

void my_SDL_init(){

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
  }

  //Enable gpu_enhanced textures
  IMG_Init(IMG_INIT_PNG);

  my_window = SDL_CreateWindow("my_game",
			       SDL_WINDOWPOS_CENTERED,
			       SDL_WINDOWPOS_CENTERED,
			       SCREEN_WIDTH,
			       SCREEN_HEIGHT, 0);
  my_renderer = SDL_CreateRenderer(my_window,-1,0);

}

int main(int argc, char* argv[])
{
  my_SDL_init();

  bool display = true;
  SDL_Texture* my_texture = NULL, *my_texture2 = NULL, *my_texture3 = NULL, *my_texture4 = NULL;
  SDL_Event event;
  SDL_Surface * image=NULL,* image2=NULL, *image3 = NULL, *image4 = NULL;
  image = IMG_Load("spaceship.PNG");
  image2 = IMG_Load("person1.PNG");
  image3 = IMG_Load("person2.PNG");
  image4 = IMG_Load("moon.PNG");

  my_texture = SDL_CreateTextureFromSurface(my_renderer, image);
  my_texture2 = SDL_CreateTextureFromSurface(my_renderer, image2);
  my_texture3 = SDL_CreateTextureFromSurface(my_renderer, image3);
  my_texture4 = SDL_CreateTextureFromSurface(my_renderer, image4);

  SDL_FreeSurface(image);
  SDL_FreeSurface(image2);
  SDL_FreeSurface(image3);
  SDL_FreeSurface(image4);



  Uint32 this_start_time = 0;
  Uint32 last_count_time = 0;
  Uint32 this_duration = 0;
  int fps_counter = 0, current_fps = 0;

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 260;
  rect.w = 100;
  rect.h = 100;

  SDL_Rect rect_person;
  rect_person.x = 455;
  rect_person.y = 400;
  rect_person.w = 75;
  rect_person.h = 75;

  SDL_Rect rect_person2;
  rect_person2.x = 100;
  rect_person2.y = 408;
  rect_person2.w = 75;
  rect_person2.h = 75;

  SDL_Rect rect_moon;
  rect_moon.x = 55;
  rect_moon.y = 79;
  rect_moon.w = 100;
  rect_moon.h = 100;

  SDL_Rect land_rect;
  land_rect.x = 0;
  land_rect.y = 400;
  land_rect.w = SCREEN_WIDTH;
  land_rect.h = SCREEN_HEIGHT;

  bool is_running = true;
  while (is_running) {
	  this_start_time = SDL_GetTicks();

	  while (SDL_PollEvent(&event)) {

		  if (event.type == SDL_QUIT) {
			  is_running = false;
		  }
	  }
	  rect.x += 5;

	  if (rect.x > SCREEN_WIDTH) rect.x = 0;

	  SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 255);
	  SDL_RenderClear(my_renderer);

	  SDL_SetRenderDrawColor(my_renderer, 0, 180, 0, 255);
	  SDL_RenderFillRect(my_renderer, &land_rect);

	  SDL_RenderCopy(my_renderer, my_texture, NULL, &rect);
	  SDL_RenderCopy(my_renderer, my_texture2, NULL, &rect_person);
	  SDL_RenderCopy(my_renderer, my_texture3, NULL, &rect_person2);
	  SDL_RenderCopy(my_renderer, my_texture4, NULL, &rect_moon);

	  SDL_RenderPresent(my_renderer);

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


  return 0;
}
