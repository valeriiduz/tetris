sdl_libs = -lSDL2 -lSDL2_image -lSDL2_mixer

compile:
	g++ -o tetris.out main.cpp $(sdl_libs)
