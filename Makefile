sdl_config = -lSDL2 -lSDL2_image

compile:
	g++ -o tetris.out main.cpp $(sdl_config)
