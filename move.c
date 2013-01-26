#include <math.h>

#include "main_sdl.h"
#include "macros.h"

int checkPosition(int map_size, int map[map_size][map_size][map_size], GLfloat x, GLfloat y, GLfloat z)
{
	int ix = (int) x;
	int iy = (int) y;
	int iz = (int) z;

	if(map[ix][iy][iz] == 0)
		return 1;
	else
		return 0;
}

GLfloat makeGoodPosition(GLfloat old, GLfloat new)
{
	GLfloat good = (float) ((int) old);

	if(new > old)
		good += 0.8f;
	else
		good += 0.2f;

	return good;
}

void changeToGoodPosition(GLfloat position[3], GLfloat new_position[3], int x, int y, int z) {
	position[0] = (x ? makeGoodPosition(position[0], new_position[0]) : new_position[0]);
	position[1] = (y ? makeGoodPosition(position[1], new_position[1]) : new_position[1]);
	position[2] = (z ? makeGoodPosition(position[2], new_position[2]) : new_position[2]);
	return;
}

void move(GLfloat position[3], int rotation[2], int map_size, int map[map_size][map_size][map_size], int direction)
{
	int check[2][2];

	float myrot = rotation[0] + direction;

	GLfloat new_position[3];
	new_position[0] = position[0] + 0.1f * sin(myrot * DEG_TO_RAD);
	new_position[1] = position[1];
	new_position[2] = position[2] - 0.1f * cos(myrot * DEG_TO_RAD);

	check[0][0] = checkPosition(map_size, map, new_position[0] - 0.2f, new_position[1], new_position[2] - 0.2f);
	check[0][1] = checkPosition(map_size, map, new_position[0] - 0.2f, new_position[1], new_position[2] + 0.2f);
	check[1][0] = checkPosition(map_size, map, new_position[0] + 0.2f, new_position[1], new_position[2] - 0.2f);
	check[1][1] = checkPosition(map_size, map, new_position[0] + 0.2f, new_position[1], new_position[2] + 0.2f);

	if(check[0][0] && check[0][1] && check[1][0] && check[1][1]) { // If we go to a free place
		changeToGoodPosition(position, new_position, 0, 0, 0);
	}
	else if(check[0][0] + check[0][1] + check[1][0] + check[1][1] == 1) { // If we go to a conner
		changeToGoodPosition(position, new_position, 1, 0, 1);
	}
	else if(check[0][0] + check[0][1] + check[1][0] + check[1][1] == 2) { // If we hit one side of an obstacle
		if((check[0][0] && check[0][1]) || (check[1][0] && check[1][1]))
			changeToGoodPosition(position, new_position, 1, 0, 0);
		else if((check[0][0] && check[1][0]) || (check[0][1] && check[1][1]))
			changeToGoodPosition(position, new_position, 0, 0, 1);
		else if((check[0][0] && check[1][1]) || (check[0][1] && check[1][0]))
			changeToGoodPosition(position, new_position, 1, 0, 1);
	}
	else if(check[0][0] + check[0][1] + check[1][0] + check[1][1] == 3) { // If we hit exactly conner of an obstacle
		if(((check[0][0] || check[0][1]) && (position[0] < new_position[0])) || // If we go to the middle of the obstacle
				((check[1][0] || check[1][1]) && (position[0] > new_position[0])))
			changeToGoodPosition(position, new_position, 0, 0, 1);
		else if(((check[0][0] || check[1][0]) && (position[2] < new_position[2])) || // IF we go to the middle of the obstacle
				((check[0][1] || check[1][1]) && (position[2] > new_position[2])))
			changeToGoodPosition(position, new_position, 1, 0, 0);
		else { // If we go around the obstacle
			int x = (int) position[0];
			if(abs(x - position[0]) + abs(x - new_position[0]) > 0.5f)
				x += 1;
			int z = (int) position[2];
			if(abs(z - position[0]) + abs(z - new_position[0]) > 0.5f)
				z += 1;
			if(abs(((float) x - position[0]) / ((float) z - position[2])) >
					abs(((float) x - new_position[0]) / ((float) z - new_position[2])))
				changeToGoodPosition(position, new_position, 1, 0, 0);
			else
				changeToGoodPosition(position, new_position, 0, 0, 2);
		}
	}

	return;
}
