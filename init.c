#include "main_sdl.h"

void InitGL(int Width, int Height) // Tuto funkci voláme hned po vytvoření okna pro inicializace OpenGL
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) { // Inicializace SDL s grafickým výstupem
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) == NULL) { // Vytvoření OpenGL okna 640x480
		fprintf(stderr, "Impossible to create OpenGL window: %s\n", SDL_GetError());
		SDL_Quit(); // Ukončení SDL
		exit(2);
	}
	if ((SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL))) {
		fprintf(stderr, "Setting keyboard repeat failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(3);
	}
	SDL_WM_SetCaption("Quadrax 3D", NULL); // Titulek okna

	glViewport(0, 0, Width, Height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Černé pozadí
	glClearDepth(1.0); // Povolíme mazání pozadí
	glDepthFunc(GL_LESS); // Vybereme typ Depth Testu
	glEnable(GL_DEPTH_TEST); // Povolíme Depth Test
	glShadeModel(GL_SMOOTH); // Povolíme Smooth Color Shading
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Resetujeme projekční matici
	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f); // Vypočítáme poměr okna
	glMatrixMode(GL_MODELVIEW);
}
