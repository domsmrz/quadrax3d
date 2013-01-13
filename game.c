#include "main_sdl.h"
#include "macros.h"
#include "init.h"
#include "move.h"
#include "draw.h"


GLfloat position[3]; // Position of player
int rotation[2]; // Rotation of player
int map[MAP_SIZE][MAP_SIZE][MAP_SIZE];

void dumpPosition()
{
	printf("Position: %f; %f; %f\n", position[0], position[1], position[2]);
	printf("Rotation: %d; %d\n", rotation[0], rotation[1]);
	return;
}

void dumpMap()
{
	int i, j;
	for(i = 0; i < 10; ++i) {
		for(j = 0; j < 10; ++j) {
			printf("%d", map[i][0][j]);
		}
		printf("\n");
	}
	printf("\n");
}

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
		case SDLK_m:
			dumpMap();
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
			move(position, rotation, map, 0);
			break;
		case SDLK_s:
			move(position, rotation, map, 180);
			break;
		case SDLK_a:
			move(position, rotation, map, 270);
			break;
		case SDLK_d:
			move(position, rotation, map, 90);
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
