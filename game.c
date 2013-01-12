#include <math.h>

#include "macros.h"
#include "main_sdl.h"
#include "init.h"
#include "draw.h"

#define MAP_SIZE 10

GLfloat position[3]; // Position of player
GLfloat rotation[2]; // Rotation of player
int map[MAP_SIZE][MAP_SIZE][MAP_SIZE];

void dumpPosition()
{
	printf("Position: %f; %f; %f\n", position[0], position[1], position[2]);
	printf("Rotation: %f; %f\n", rotation[0], rotation[1]);
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

int checkPosition(GLfloat x, GLfloat y, GLfloat z)
{
	int ix = (int) x;
	int iy = (int) y;
	int iz = (int) z;

	if(map[ix][iy][iz] == 0)
		return 1;
	else
		return 0;
}

void move(int direction)
{
	int check[2][2];

	float myrot = rotation[0] + direction;

	GLfloat new_position[3];
	new_position[0] = position[0] + 0.1f * sin(myrot * DEG_TO_RAD);
	new_position[1] = position[1];
	new_position[2] = position[2] - 0.1f * cos(myrot * DEG_TO_RAD);

	check[0][0] = checkPosition(new_position[0] - 0.2f, new_position[1], new_position[2] - 0.2f);
	check[0][1] = checkPosition(new_position[0] - 0.2f, new_position[1], new_position[2] + 0.2f);
	check[1][0] = checkPosition(new_position[0] + 0.2f, new_position[1], new_position[2] - 0.2f);
	check[1][1] = checkPosition(new_position[0] + 0.2f, new_position[1], new_position[2] + 0.2f);

	if(check[0][0] && check[0][1] && check[1][0] && check[1][1]) {
		position[0] = new_position[0];
		position[1] = new_position[1];
		position[2] = new_position[2];
	}

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
