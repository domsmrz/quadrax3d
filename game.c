#include <math.h>

#include "main_sdl.h"
#include "init.h"
#include "draw.h"

#define MAP_SIZE 10

GLfloat position[3]; // Position of player
GLfloat rotation[2]; // Rotation of player
int map[MAP_SIZE][MAP_SIZE][MAP_SIZE];

void loadMap()
{
	FILE* map_file = fopen("map.map", "r");
	int i, j, k, a, b, c;

	fscanf(map_file, "%d%d%d", &a, &b, &c);
	position[0] = (float) a + 0.5f;
	position[1] = (float) b;
	position[2] = (float) c + 0.5f;

	rotation[0] = 0;
	rotation[1] = 0;

	for(i = 0; i < MAP_SIZE; ++i)
		for(j = 0; j < MAP_SIZE; ++j)
			for(k = 0; k < MAP_SIZE; ++k)
				fscanf(map_file, "%d", &map[i][j][k]);

	fclose(map_file);

	return;
}

void DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Vymazání obrazovkového a hloubkového bufferu
	glLoadIdentity(); // Reset matice pohledu

	drawMap(MAP_SIZE, map, position, rotation);

	SDL_GL_SwapBuffers(); // Prohozeni bufferu, aby se zobrazilo, co jsme nakreslili

	return;
}

void move(int direction)
{
	const float degtorad = 0.0174532925f;
	float myrot = rotation[0] + direction;
	position[0] += 0.1f * sin(myrot * degtorad);
	position[2] -= 0.1f * cos(myrot * degtorad);

	return;
}

void dumpPosition()
{
	printf("Position: %f; %f; %f\n", position[0], position[1], position[2]);
	printf("Rotation: %f; %f\n", rotation[0], rotation[1]);
	return;
}

void handleKeyPress(SDL_keysym *keysym)
{
	switch (keysym->sym)
	{
		case SDLK_ESCAPE:
		case SDLK_q:
			exit(0);
			break;
		case SDLK_e:
			dumpPosition();
			break;

		// Rotations
		case SDLK_UP:
			rotation[1] -= 1;
			if(rotation[1] < -90)
				rotation[1] = -90;
			break;
		case SDLK_DOWN:
			rotation[1] += 1;
			if(rotation[1] > 90)
				rotation[1] = 90;
			break;
		case SDLK_LEFT:
			rotation[0] -= 1;
			if(rotation[0] < 0)
				rotation[0] += 360;
			break;
		case SDLK_RIGHT:
			rotation[0] += 1;
			if(rotation[0] >= 360)
				rotation[0] -= 360;
			break;

		// Moves
		case SDLK_w:
			move(0);
			break;
		case SDLK_s:
			move(180);
			break;
		case SDLK_a:
			move(270);
			break;
		case SDLK_d:
			move(90);
			break;
		default:
			break;
	}
	return;
}

int main()
{
	InitGL(640, 480);
	int done = 0;
	loadMap();
	while (!done) { // Hlavní cyklus programu
		DrawGLScene(); // Vykreslení scény
		SDL_Event event; // Proměnná zprávy
		while (SDL_PollEvent(&event)) { // Zpracovávat zprávy
			if (event.type == SDL_QUIT) { // Zpráva o ukončení
				done = 1; // Ukončit hlavní cyklus
				}
			if (event.type == SDL_KEYDOWN) { // Zpráva o stisku klávesy
				handleKeyPress(&event.key.keysym);
			}
		}
	}
	SDL_Quit(); // Ukončení SDL
	return 0;
}
