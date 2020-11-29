#include "game_engine.h"

Engine::Engine(){}

void Engine::init(){

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
  player = new GameObject();
  part_blow = new ParticleEmitter();

  player->obj_init("spaceship.png",my_renderer);
  player->stationary_obj_init("moon.PNG",my_renderer);

  //this is the green land that is shown in game
  land_rect.x = 0;
  land_rect.y = 400;
  land_rect.w = SCREEN_WIDTH;
  land_rect.h = SCREEN_HEIGHT;

}
//handle events loop that will keep track of game being played and
//user input
void Engine::handleEvents(){

  SDL_Event game_event;
  SDL_PollEvent(&game_event);
  if(game_event.type == SDL_QUIT) {game_is_running = false;}
  if(game_event.type == SDL_KEYDOWN) {cout<<"keypressed\n";}

  switch(game_event.key.keysym.sym){
    // a is to move left
    case(SDLK_a):
      player->obj_set_x_value(player->obj_get_x_value()-2);
      break;
    //d is to move right
    case(SDLK_d):
      player->obj_set_x_value(player->obj_get_x_value()+2);
      break;
    //w is to move up
    case(SDLK_w):
      player->obj_set_y_value(player->obj_get_y_value()-2);
      break;
    //s is to move down
    case(SDLK_s):
      player->obj_set_y_value(player->obj_get_y_value()+2);
      break;

    default:
      //this is the code gave in class that helps with smooth transitions
      int temp_y_vel = player->obj_get_y_value();
      int temp_x_vel = player->obj_get_x_value();
      if(temp_x_vel<0){
        player->obj_set_x_value(temp_x_vel+1);
        }
      if(temp_y_vel<0){
        player->obj_set_y_value(temp_y_vel+1);
      }
      if(temp_x_vel > 0){
        player->obj_set_x_value(temp_x_vel-1);
      }
     if(temp_y_vel > 0){
        player->obj_set_y_value(temp_y_vel-1);
      }
      part_blow->pe_quit();
      
    break;
  }


}
void Engine::updateMechanics(){
  //call the updates from the GameObject class
  player->obj_update();

  //if the ship has hit object then explode and restart
  if(DEAD == player->obj_get_state()){
    int temp_x = player->obj_get_x_pos();
    int temp_y = player->obj_get_y_pos();
    part_blow->pe_init("explosion.png",my_renderer,temp_x,temp_y,80,80,PART_TYPE_BLOW);

    player->obj_set_x_pos(STARTING_POS_X);
    player->obj_set_y_pos(STARTING_POS_Y);
    player->obj_set_x_value(0);
    player->obj_set_y_value(0);

  }

}

void Engine::render(){
  //make dark background
  SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 255);
  SDL_RenderClear(my_renderer);
  //render in the "land"
  SDL_SetRenderDrawColor(my_renderer, 0, 180, 0, 255);
  SDL_RenderFillRect(my_renderer, &land_rect);

  player->moon_render(my_renderer);
  //render explosions
  part_blow->pe_render(my_renderer);
  //call GameObject render that handles sprites and movement
  player->obj_render(my_renderer);

  //diisplay render
  SDL_RenderPresent(my_renderer);
}
//clean up
void Engine::quit(){
  SDL_DestroyRenderer(my_renderer);
  SDL_DestroyWindow(my_window);
  part_blow->pe_quit();
  IMG_Quit();
  SDL_Quit();

}
//see if the game is still running
bool Engine::getGameRunning(){
  return game_is_running;
}
