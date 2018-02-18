#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <vector>

class Sprite {

private:

    SDL_Surface *image;
    SDL_Rect rect;

    int origin_x, origin_y;
    
public:

    Sprite( Uint32 color, int x, int y, int w = 40, int h = 40) {
	image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	SDL_FillRect( image, NULL, color );

	rect = image->clip_rect;

	origin_x = 0;
	origin_y = 0;
	
	rect.x = x - origin_x;
	rect.y = y - origin_y;
    }

    void update() {
	
    }

    void draw( SDL_Surface *destionation ) {
	SDL_BlitSurface( image, NULL, destionation, &rect );
    }

    SDL_Surface* get_image() const {

	return image;
    }

    bool operator == ( const Sprite &other) const {
	
	return ( image == other.image );
    }
    
};
