#include "GLUT.h"
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include "Point2D.h"
#include "Room.h"
#include "Node.h"
#include "CompareNodes.h"
#include "Parent.h"
#include "ConstValue.h"
#include "Storage.h" 
#include "Door.h" 
#include "Warrior.h" 
#include "Maze.h"

using namespace std;

//temp
int counter = 0;

const int W = 600; // window width
const int H = 600; // window height
const int NUM_ROOMS = 10;

const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

const int RED = 11;
const int GREEN = 12;
const int BLUE = 13;
const int YELLO = 14;
const int ORANGE = 15;
const int GREY = 16;
const int PINK = 17;
const int PURPLE = 18;
const int BLACK = 19;
const int BROWN = 20;

static const int MSIZE = Maze::MSIZE;
const double SQSIZE = 2.0 / MSIZE;

Warrior *warriors[ConstValue::NUM_OF_WARRIORS];

Point2D start,target;

Maze* maze;

void drawWarrior(const Warrior &warrior);
void createWarriors();

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 10 * number_of_seconds;

	// Stroing start time 
	clock_t start_time = clock();

	// looping till required time is not acheived 
	while (clock() < start_time + milli_seconds);

}

void init()
{
	maze = &Maze::getInstance();
	createWarriors();

	glClearColor(0.7, 0.7, 0.7, 0);
	glOrtho(-1, 1, -1, 1, -1, 1);
}

void createWarriors()
{
	srand(time(0));

	for (int i = 0; i < ConstValue::NUM_OF_WARRIORS; i++)
	{
		Room& r = maze->getRooms()[rand() % Maze::NUM_ROOMS];
		int y = r.GetCenter().GetY();
		int x = r.GetCenter().GetX();
		maze->parts[y][x].setType(MazePart::WARRIOR);
		Warrior *w = new Warrior(r, *new Point2D(x, y));
		warriors[i] = w;
		drawWarrior(*warriors[i]);
	}
}

void drawWarrior(const Warrior &warrior)
{
	Point2D location = warrior.getLocation();
	maze->parts[location.GetY()][location.GetX()].setType(MazePart::WARRIOR);
}

void DrawMaze()
{
	int i, j;

	for(i = 0;i<MSIZE;i++)
		for (j = 0; j < MSIZE; j++)
		{
			switch (maze->parts[i][j].getType())
			{
			case MazePart::WALL:
				glColor3d(0.4, 0, 0); // dark red;
				break;
			case MazePart::SPACE:
				glColor3d(1, 1, 1); // white;
				break;
			case MazePart::VISITED:
				glColor3d(0, 0.9, 0); // green;
				break;
			case MazePart::TARGET:
				glColor3d(1,0,0 ); // RED;
				break;
			case MazePart::GRAY:
				glColor3d(1, .8, 0); // ORANGE;
				break;
			case MazePart::MEDICAL:
				glColor3d(0,0,1); //blue
				break;
			case MazePart::AMMO:
				glColor3d(1,0,0); //red
				break;
			case MazePart::WARRIOR:
				glColor3d(0, 0, 0); // BLACK
				break;

			}
			// draw square
			glBegin(GL_POLYGON);
				glVertex2d(j*SQSIZE - 1- SQSIZE/2, i*SQSIZE - 1+SQSIZE/2);
				glVertex2d(j*SQSIZE - 1 + SQSIZE / 2, i*SQSIZE - 1 + SQSIZE / 2);
				glVertex2d(j*SQSIZE - 1 + SQSIZE / 2, i*SQSIZE - 1 - SQSIZE / 2);
				glVertex2d(j*SQSIZE - 1 - SQSIZE / 2, i*SQSIZE - 1 - SQSIZE / 2);
			glEnd();
		}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	DrawMaze();

	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	if (!warriors[0]->isAlive() || !warriors[1]->isAlive())
		return;

	// temp
	(warriors[0])->selectMission(*warriors[1]);
	(warriors[1])->selectMission(*warriors[0]);

	/*(warriors[0])->lookForMedicalStorage();
	(warriors[1])->lookForMedicalStorage();*/

	glutPostRedisplay(); // calls indirectly to display
	delay(5);
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // idle: when nothing happens
	init();

	glutMainLoop();
}


