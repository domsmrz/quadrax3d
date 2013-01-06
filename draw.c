#include "main_sdl.h"

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

void drawBlock1x1(GLfloat x, GLfloat y, GLfloat z)
{
	glColor3f(0.0f, 1.0f, 0.0f);
	drawSquare(0.0f+x, 0.0f+y, 0.0f+z, 0.0f+x, 1.0f+y, 1.0f+z);
	drawSquare(0.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 0.0f+y, 1.0f+z);
	drawSquare(0.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 0.0f+z);
	drawSquare(0.0f+x, 0.0f+y, 1.0f+z, 1.0f+x, 1.0f+y, 1.0f+z);
	drawSquare(0.0f+x, 1.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 1.0f+z);
	drawSquare(1.0f+x, 0.0f+y, 0.0f+z, 1.0f+x, 1.0f+y, 1.0f+z);
}

void drawMap(int size, int map[size][size][size], GLfloat* position, GLfloat* rotation)
{
	int i, j, k;

	glRotatef(rotation[0], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[1], 1.0f, 0.0f, 0.0f);
	glTranslatef(-position[0], -position[1], -position[2]);

	for(i = 0; i < size; ++i)
		for(j = 0; j < size; ++j)
			for(k = 0; k < size; ++k)
				if(map[i][j][k] == 1)
					drawBlock1x1(i, j, k);

	return;
}
