#include <math.h>

#include "macros.h"
#include "main_sdl.h"

GLuint textures[1];

void loadTexture()
{
	GLuint texture;
	SDL_Surface* image;

	image = SDL_LoadBMP("graphics/base.bmp");
	//image = IMG_Load("graphics/base.png");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textures[0] = texture;
}

void drawSquare(GLfloat ax, GLfloat ay, GLfloat az, GLfloat bx, GLfloat by, GLfloat bz)
{
	if(ax == bx) {
		glBegin(GL_QUADS);
			glVertex3f(ax, ay, az);
			glVertex3f(ax, ay, bz);
			glVertex3f(ax, by, bz);
			glVertex3f(ax, by, az);
		glEnd();
	}
	else if(ay == by) {
		glBegin(GL_QUADS);
			glVertex3f(ax, ay, az);
			glVertex3f(ax, ay, bz);
			glVertex3f(bx, ay, bz);
			glVertex3f(bx, ay, az);
		glEnd();
	}
	else if(az == bz) {
		glBegin(GL_QUADS);
			glVertex3f(ax, ay, az);
			glVertex3f(ax, by, az);
			glVertex3f(bx, by, az);
			glVertex3f(bx, ay, az);
		glEnd();
	}
	else
		printf("Warning: Wrong usage of drawSquare()!\n");
	return;
}

void drawSquareTextured(GLfloat ax, GLfloat ay, GLfloat az, GLfloat bx, GLfloat by, GLfloat bz)
{
	if(ax == bx) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, az);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ax, ay, bz);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(ax, by, bz);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(ax, by, az);
		glEnd();
	}
	else if(ay == by) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, az);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ax, ay, bz);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(bx, ay, bz);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(bx, ay, az);
		glEnd();
	}
	else if(az == bz) {
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ax, ay, az);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ax, by, az);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(bx, by, az);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(bx, ay, az);
		glEnd();
	}
	else
		printf("Warning: Wrong usage of drawSquare()!\n");
	return;
}

void drawBlock1x1(GLfloat x, GLfloat y, GLfloat z)
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	drawSquareTextured(0.0f+x, 0.0f+y, 1.0f+z, 0.0f+x, 1.0f+y, 0.0f+z); // levá stěna
	drawSquareTextured(0.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 0.0f+z); // přední stěna
	drawSquareTextured(1.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 1.0f+z); // pravá stěna
	drawSquareTextured(1.0f+x, 0.0f+y, 1.0f+z, 0.0f+x, 1.0f+y, 1.0f+z); // zadní stěna
	drawSquareTextured(0.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 0.0f+y, 1.0f+z); // dolní stěna
	drawSquareTextured(0.0f+x, 1.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 1.0f+z); // horní stěna
}

void drawMap(int size, int map[size][size][size], GLfloat position[3], int rotation[2])
{
	int i, j, k;

	glRotatef(rotation[0], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[1], cos(rotation[0] * DEG_TO_RAD), 0.0f, sin(rotation[0] * DEG_TO_RAD));
	glTranslatef(-position[0], -position[1]-1.5f, -position[2]);

	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			for(k = 0; k < size; ++k)
				if(map[i][j][k] == 1)
					drawBlock1x1(i, j, k);

	return;
}
