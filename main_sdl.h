#ifndef _MAIN_SDL_H
#define _MAIN_SDL_H

#ifdef WIN32 // Pokud se bude kompilovat program po Windows
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h> // Hlavičkový soubor pro Windows
#endif
#if defined(__APPLE__) && defined(__MACH__) // Pokud se bude kompilovat program pro Apple
	#include <OpenGL/gl.h> // Hlavičkový soubor pro OpenGL32 knihovnu v Applu
	#include <OpenGL/glu.h> // Hlavičkový soubor pro GLu32 knihovnu v Applu
#else
	#include <GL/gl.h> // Hlavičkový soubor pro OpenGL32 knihovnu
	#include <GL/glu.h> // Hlavičkový soubor pro GLu32 knihovnu
#endif
#include "SDL.h" // Hlavičkový soubor pro SDL
#include "SDL_image.h"

#endif
