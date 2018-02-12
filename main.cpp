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
    SDL_Surface *screen = SDL_GetWindowSurface( Window );

    const Uint32 color_7f3b08 = SDL_MapRGB( screen->format, 127, 59, 8);
    const Uint32 color_b35806 = SDL_MapRGB( screen->format, 179, 88, 6);
    const Uint32 color_e08214 = SDL_MapRGB( screen->format, 224, 130, 20);
    const Uint32 color_fdb863 = SDL_MapRGB( screen->format, 253, 184, 99);
    const Uint32 color_fee0b6 = SDL_MapRGB( screen->format, 254, 224, 182);
    const Uint32 color_f7f7f7 = SDL_MapRGB( screen->format, 247, 247, 247);
    const Uint32 color_d8daeb = SDL_MapRGB( screen->format, 216, 218, 235);
    const Uint32 color_b2abd2 = SDL_MapRGB( screen->format, 178, 171, 210);
    const Uint32 color_8073ac = SDL_MapRGB( screen->format, 128, 115, 172);
    const Uint32 color_542788 = SDL_MapRGB( screen->format, 84, 39, 136);
    const Uint32 color_2d004b = SDL_MapRGB( screen->format, 45, 0, 75);
    
    const double fps = 10;
    Uint32 starting_tick;
    SDL_Event event;
    int x, y, w, h;
    bool running = true;
    
    int top_px = 0;
    int left_px = 0*5;
    
    int dasboard[10][15] = {0,0};

    int top_col = 0;
    int left_col = 0;

    while(running){

	SDL_FillRect(screen, NULL, color_f7f7f7);

	Sprite panel( color_d8daeb, (700 - 300), 0, 300, 600);
	panel.draw( screen );

	starting_tick = SDL_GetTicks();

	Uint32 col = SDL_MapRGB( screen->format, 128, 115, 172 );

	Sprite cub(col, left_px, top_px);
	Sprite cub1(col, left_px+(40*1), top_px);
	Sprite cub2(col, left_px+(40*2), top_px);
	Sprite cub3(col, left_px+(40*3), top_px);
	
	SpriteGroup sprites;
	sprites.add( &cub );
	sprites.add( &cub1 );
	sprites.add( &cub2 );
	sprites.add( &cub3 );
	sprites.add( &panel );

	sprites.draw( screen );

	top_px += 40;

	/*dasboard[top_col-1][0] = 0 ;
	  dasboard[top_col-1][1] = 0;
	  dasboard[top_col-1][2] = 0;
	  dasboard[top_col-1][3] = 0;

	  dasboard[top_col][0] = 1;
	  dasboard[top_col][1] = 1;
	  dasboard[top_col][2] = 1;
	  dasboard[top_col][3] = 1;

	  //top_col += 1;
	  */
	if (top_px >= 600) {
		left_px += 40;
		top_px = 0;
		top_col = 0;
	    }
	
	if ((1000 / fps) - SDL_GetTicks() - starting_tick)
	    SDL_Delay( 1000 / fps - (SDL_GetTicks() - starting_tick));
	
	SDL_GetWindowPosition(Window, &x, &y);
	cout<<"X: "<<x<<" Y: "<<y<<endl;

	for (int i = 0; i < 10; i++ ) {
	    
	    for (int p = 0; p < 15; p++) {

		cout<<" "<<dasboard[i][p];
	    }
	    cout<<'\n';
	}

	SDL_UpdateWindowSurface(Window);
	
	while(SDL_PollEvent(&event)){

	    if(event.type == SDL_KEYDOWN) {
		SDL_Delay(1000);
	    }
	    
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
