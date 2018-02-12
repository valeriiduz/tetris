sdl_libs = -lSDL2 -lSDL2_image -lSDL2_mixer
#sprites = Sprite.cpp SpriteGroup.cpp

compile:
	g++ -o tetris.out main.cpp $(sprites) $(sdl_libs)
