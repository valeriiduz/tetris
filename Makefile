sdl_config = `sdl2-config --cflags --libs`

compile:
	g++ -o tetris.out main.cpp $(sdl_config)
