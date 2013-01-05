#include <stdio.h>

#include "main_sdl.h"
#include "init.h"
#include "draw.h"

void DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Vymazání obrazovkového a hloubkového bufferu
	glLoadIdentity(); // Reset matice pohledu

	drawMap();

	SDL_GL_SwapBuffers(); // Prohozeni bufferu, aby se zobrazilo, co jsme nakreslili

	return;
}

int main()
{
	InitGL(640, 480);
	int done = 0;
	while (!done) { // Hlavní cyklus programu
		DrawGLScene(); // Vykreslení scény
		SDL_Event event; // Proměnná zprávy
		while (SDL_PollEvent(&event)) { // Zpracovávat zprávy
			if (event.type == SDL_QUIT) { // Zpráva o ukončení
				done = 1; // Ukončit hlavní cyklus
				}
			if (event.type == SDL_KEYDOWN) { // Zpráva o stisku klávesy
				//handleKeyPress(&event.key.keysym);
			}
		}
	}
	SDL_Quit(); // Ukončení SDL
	return 0;
}
