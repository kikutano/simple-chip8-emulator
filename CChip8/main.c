#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "decoder.h"

void handleInput(const SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		int key = -1;
		switch (event->key.keysym.sym)
		{
		case SDLK_x: key = 0; break;
		case SDLK_1: key = 1; break;
		case SDLK_2: key = 2; break;
		case SDLK_3: key = 3; break;
		case SDLK_q: key = 4; break;
		case SDLK_w: key = 5; break;
		case SDLK_e: key = 6; break;
		case SDLK_a: key = 7; break;
		case SDLK_s: key = 8; break;
		case SDLK_d: key = 9; break;
		case SDLK_z: key = 10; break;
		case SDLK_c: key = 11; break;
		case SDLK_4: key = 12; break;
		case SDLK_r: key = 13; break;
		case SDLK_f: key = 14; break;
		case SDLK_v: key = 15; break;
		default: break;
		}

		if (key != -1)
		{
			keyPressed(key);
		}
	}
	else if (event->type == SDL_KEYUP)
	{
		int key = -1;
		switch (event->key.keysym.sym)
		{
		case SDLK_x: key = 0; break;
		case SDLK_1: key = 1; break;
		case SDLK_2: key = 2; break;
		case SDLK_3: key = 3; break;
		case SDLK_q: key = 4; break;
		case SDLK_w: key = 5; break;
		case SDLK_e: key = 6; break;
		case SDLK_a: key = 7; break;
		case SDLK_s: key = 8; break;
		case SDLK_d: key = 9; break;
		case SDLK_z: key = 10; break;
		case SDLK_c: key = 11; break;
		case SDLK_4: key = 12; break;
		case SDLK_r: key = 13; break;
		case SDLK_f: key = 14; break;
		case SDLK_v: key = 15; break;
		default: break;
		}

		if (key != -1)
		{
			keyReleased(key);
		}
	}
}

void drawFrameScreen(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int i = 0; i < 64; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			if (screenData[i][j] > 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
			else {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(0);
}

const int LOGICAL_WIDTH = 64;
const int LOGICAL_HEIGHT = 32;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* romName = "C:\\Users\\gaetano.lenoci\\source\\repos\\Personals\\CChip8\\CChip8\\TestRoms\\4-flags.ch8";

int main() {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error during SDL init: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Chip 8 Emulator 0.9.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LOGICAL_WIDTH * 15, LOGICAL_HEIGHT * 15, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!window) {
		printf("Error during window creation: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Errore nella creazione del renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

	int running = 1;
	SDL_Event event;

	init();
	loadGame(romName);
	clearScreen();

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}

			handleInput(&event);
		}

		processNextOpcode();
		drawFrameScreen(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}