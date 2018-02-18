sdl_libs = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

default:
	@echo 'Makefile for Tetris game'
	@echo 'if you want compile programm use:'
	@echo 'make compile'
	@echo

compile:
	@echo 'Start compile'
	---- g++ -o tetris.out main.cpp $(sdl_libs)
	@echo 'Finish compile'
