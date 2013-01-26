#ifndef _DRAW_H
#define _DRAW_H
void loadTexture();
void drawSquare(GLfloat ax, GLfloat ay, GLfloat az, GLfloat bx, GLfloat by, GLfloat bz);
void drawSquareTextured(GLfloat ax, GLfloat ay, GLfloat az, GLfloat bx, GLfloat by, GLfloat bz);
void drawBlock1x1(GLfloat x, GLfloat y, GLfloat z);
void drawMap(int size, int map[size][size][size], GLfloat position[3], int rotation[2]);
#endif
