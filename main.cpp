#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

// Using for debuging
#include <iostream>
using namespace std;

#include "Sprite.hpp"
#include "SpriteGroup.hpp"

SDL_Surface *Window_Logo () {

    // Declare an SDL_Surface to be filled in
    // with pixel data from an image file
    SDL_Surface *Image = IMG_Load("src/logo.jpg");
    
    if(!Image) {
	// Handle error
	printf("IMG_Load: %s\n", IMG_GetError());
    }

    return Image; 
}

void Theme_Audio () {

    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
	printf("Mix_OpenAudio: %s\n", Mix_GetError());
	exit(2);
    }

    // load the MP3 file "music.mp3" to play as music
    Mix_Music *music = Mix_LoadMUS("src/background.wav");
    if(!music) {
	printf("Mix_LoadMUS(\"src/background.wav\"): %s\n", Mix_GetError());
	// this might be a critical error...
    }

    if(Mix_PlayMusic(music, -1)==-1) {
	printf("Mix_PlayMusic: %s\n", Mix_GetError());
	// well, there's no music, but most games don't break without music...
    }
}

int main (int argc, char *argv[]) {
  
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *Window = SDL_CreateWindow( "Tetris",
					   SDL_WINDOWPOS_UNDEFINED,
					   SDL_WINDOWPOS_UNDEFINED,
					   700,
					   600,
					   SDL_WINDOW_RESIZABLE);
    
    // Created logo for window
    SDL_Surface *Image = Window_Logo();
    // The icon is attached to the window pointer
    SDL_SetWindowIcon(Window, Image);

    // Load and play theme audio
    Theme_Audio();
    
    //SDL_SetWindowBordered(window, SDL_FALSE);
    SDL_Surface *screen = SDL_GetWindowSurface(Window);

    Uint32 background = SDL_MapRGB(screen->format, 32,32,32);

    SDL_FillRect(screen, NULL, background);
    
    const double fps = 60;
    Uint32 starting_tick;
    SDL_Event event;
    int x, y, w, h;
    bool running = true;

    while(running){

	starting_tick = SDL_GetTicks();

	Uint32 col = SDL_MapRGB(screen->format, 0,0,32);
	Sprite object(col, 700/2, 600/2);
	Sprite cub(col, 70, 60);
	
	SpriteGroup sprites;
	sprites.add( &object );
	sprites.add( &cub );

	sprites.draw( screen );
	
	if ((1000 / fps) - SDL_GetTicks() - starting_tick)
	    SDL_Delay( 1000 / fps - (SDL_GetTicks() - starting_tick));
	
	SDL_GetWindowPosition(Window, &x, &y);
	cout<<"X: "<<x<<" Y: "<<y<<endl;

	SDL_UpdateWindowSurface(Window);
	
	while(SDL_PollEvent(&event)){
	    if(event.type == SDL_QUIT){
		running = false;
		break;
	    }
	}
    }

    SDL_DestroyWindow(Window);

    Mix_Quit();
    SDL_Quit();
  
    return 0;
}
