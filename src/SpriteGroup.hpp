#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <vector>

class SpriteGroup {

private:
    
    vector <Sprite*> sprites;
    int sprites_size;

public:

    SpriteGroup copy() {
	
	SpriteGroup new_group;

	for( int i = 0; i < sprites_size; i++ ){
	    
	    new_group.add( sprites[i] );
	}

	return new_group;
    }

    void add(Sprite *sprite) {
	
	sprites.push_back( sprite );
	sprites_size = sprites.size();
    }

    void remove( Sprite sprite_object ) {

	for ( int i = 0; i < sprites_size; i++ ) {

	    if ( *sprites[i] == sprite_object ) {

		sprites.erase( sprites.begin() + i );
	    }
	}
	
	sprites_size = sprites.size();
    }

    bool has ( Sprite sprite_object ) {

	for ( int i = 0; i < sprites_size; i++ ) {

	    if ( *sprites[i] == sprite_object ) {

		return true;
	    }
	}

	return false;
    }

    void update ( Sprite sprite_object ) {

	if( !sprites.empty() ) {

	    for ( int i = 0; i < sprites_size; i++ ) {

		sprites[i]->update();
	    }
	}
    }

    void draw ( SDL_Surface *destionation ) {
	
	if( !sprites.empty() ) {

	    for ( int i = 0; i < sprites_size; i++ ) {

		sprites[i]->draw( destionation );
	    }
	}
    }

    void empty ( Sprite sprite_object ) {

	sprites.clear();
	sprites_size = sprites.size();
    }

    int size() {

	return sprites_size;
    }
    
    vector <Sprite*> get_prites() {
	return sprites;
    }  
};
