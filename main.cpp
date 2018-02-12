#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>
using namespace std;

int main (int argc, char *argv[]) {
  
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window;

  window = SDL_CreateWindow( "Tetris",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     700,
			     600,
			     SDL_WINDOW_RESIZABLE);

      SDL_Surface *Image;     // Declare an SDL_Surface to be filled in with pixel data from an image file

  Image = IMG_Load("src/logo.jpg");

  if(!Image) {
    // Handle error
    printf("IMG_Load: %s\n", IMG_GetError());
  }
  // The icon is attached to the window pointer
  SDL_SetWindowIcon(window, Image);

  //SDL_SetWindowBordered(window, SDL_FALSE);
  SDL_Surface *screen = SDL_GetWindowSurface(window);

  Uint32 white = SDL_MapRGB(screen->format, 32,32,32);

  SDL_FillRect(screen, NULL, white);

  SDL_UpdateWindowSurface(window);
  
  SDL_Event event;

  int x, y, w, h;
  
  bool running = true;

  while(running){

    while(SDL_PollEvent(&event)){

      if(event.type == SDL_QUIT){
	running = false;
	break;
      }
    }
    SDL_GetWindowPosition(window, &x, &y);
    //cout<<"X: "<<x<<" Y: "<<y<<endl;
  }

  //SDL_Delay(5000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
