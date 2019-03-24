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

static const int MSIZE = ConstValue::MSIZE;
const double SQSIZE = 2.0 / MSIZE;

Warrior *warriors[ConstValue::NUM_OF_WARRIORS];

Point2D start,target;

Maze &maze;

void drawWarrior(const Warrior &warrior);

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
	/// create maze
	maze = Maze::getInstance();
	createWarriors();

	/*int h= 11;
	for (int i = 0; i < 10; i++)
	{
		maze[all_rooms[i].GetCenter().GetY()][all_rooms[i].GetCenter().GetX()] = h;
		h++;
	}*/

	glClearColor(0.7, 0.7, 0.7, 0);
	glOrtho(-1, 1, -1, 1, -1, 1);
}

void createWarriors()
{
	srand(time(0));

	for (int i = 0; i < ConstValue::NUM_OF_WARRIORS; i++)
	{
		Room& r = maze.getRooms()[rand() % ConstValue::NUM_ROOMS];
		int y = r.GetCenter().GetY();
		int x = r.GetCenter().GetX();
		maze.getParts()[y][x] = ConstValue::WARRIOR;
		Warrior *w = new Warrior(r, *new Point2D(x, y));
		warriors[i] = w;
		drawWarrior(*warriors[i]);
	}
}

void drawWarrior(const Warrior &warrior)
{
	Point2D location = warrior.getLocation();
	maze.getParts()[location.GetY()][location.GetX()] = ConstValue::WARRIOR;
}

void DrawMaze()
{
	int i, j;

	for(i = 0;i<MSIZE;i++)
		for (j = 0; j < MSIZE; j++)
		{
			switch (maze.getParts()[i][j])
			{
			case ConstValue::WALL:
				glColor3d(0.4, 0, 0); // dark red;
				break;
			case ConstValue::SPACE:
				glColor3d(1, 1, 1); // white;
				break;
			case ConstValue::VISITED:
				glColor3d(0, 0.9, 0); // green;
				break;
			case ConstValue::START:
				glColor3d(0, 0, 1); // blue;
				break;
			case ConstValue::TARGET:
				glColor3d(1,0,0 ); // RED;
				break;
			case ConstValue::GRAY:
				glColor3d(1, .8, 0); // ORANGE;
				break;
			case ConstValue::MEDICAL:
				glColor3d(0,0,1); //blue
				break;
			case ConstValue::AMMO:
				glColor3d(1,0,0); //red
				break;
			case ConstValue::WARRIOR:
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
	// temp
	(warriors[0])->selectMission(*warriors[1]);
	
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


//void saveMazeToFile()
//{
//	ofstream myfile;
//	myfile.open("maze.txt");
//	myfile << MSIZE << " ";
//	myfile << MSIZE << " ";
//
//	for (int i = 0; i < MSIZE; i++)
//	{
//		for( int j = 0; j < MSIZE; j++)
//			myfile << maze[i][j] << " ";
//	}
//	//myfile << maze[i][j] << " ";
//	myfile.close();
//
//
//	ofstream f;
//	f.open("rooms.txt");
//	f << 10 << " ";
//
//	for (int i = 0; i < 10; i++)
//	{
//			f << all_rooms[i].GetCenter().GetX() << " " 
//				<< all_rooms[i].GetCenter().GetY() << " " 
//				<< all_rooms[i].GetHeight() << " "
//				<< all_rooms[i].GetWidth() << " " ;
//	}
//	//myfile << maze[i][j] << " ";
//	f.close();
//}

//void readMazeFromFile()
//{
//	// maze
//	ifstream myfile;
//	myfile.open("maze.txt");
//	int col;
//	int row;
//	myfile >> col;
//	myfile >> row;
//
//	for (int i = 0; i < MSIZE; i++)
//	{
//		for (int j = 0; j < MSIZE; j++)
//		{
//			myfile >> maze[i][j];	
//			//myfile >> tmp;
//		}
//	}
//	myfile.close();
//
//	// rooms
//	myfile.open("rooms.txt");
//	int size, x, y, h, w;
//
//	myfile >> size;
//
//	for (int i = 0; i < NUM_ROOMS; i++)
//	{
//		myfile >> x;
//		myfile >> y;
//		myfile >> h;
//		myfile >> w;
//		int idx = i + 1;
//		all_rooms[i] = *new Room(idx ,*new Point2D(x, y), w, h);
//	}
//	myfile.close();
//
//	// doors
//	myfile.open("doors2.txt");
//	int from, to, x1, y1, x2, y2;
//	int room_num;
//	myfile >> size;
//
//	//read doors: sorceRoom ,enter and exit location of the doors and vactor with all the destionations
//	for (int i = 0; i < size; i++)
//	{
//		myfile >> from;
//		myfile >> x1;
//		myfile >> y1;
//		myfile >> x2;
//		myfile >> y2;
//		myfile >> room_num;	
//		Door* door = new Door(all_rooms[from - 1],*new Point2D(x1, y1), *new Point2D(x2, y2));
//		
//		for (int j = 0; j < room_num; j++) {
//			int roomIndex;
//			myfile >> roomIndex;
//			door->addDestination(all_rooms[roomIndex-1]);
//		}
//		all_rooms[from - 1].addDoor(*door);
//	}
//	myfile.close();
//}

//void AddNewNode(Node current, int direction)
//{
//	Node* tmp;
//	Point2D* pt;
//	vector<Point2D>::iterator gray_it;
//	vector<Point2D>::iterator black_it;
//	double space_weight = 0.1, wall_weight = 5, weight;
//	int dx, dy;
//
//	switch (direction)
//	{
//	case UP:
//		dx = 0;
//		dy = -1;
//		break;
//	case DOWN:
//		dx = 0;
//		dy = 1;
//		break;
//	case LEFT:
//		dx = -1;
//		dy = 0;
//		break;
//	case RIGHT:
//		dx = 1;
//		dy = 0;
//		break;
//	} // switch
//
//	if (direction == UP && current.GetPoint().GetY() > 0 ||
//		direction == DOWN && current.GetPoint().GetY() < MSIZE - 1 ||
//		direction == LEFT && current.GetPoint().GetX() > 0 ||
//		direction == RIGHT && current.GetPoint().GetX() < MSIZE - 1)
//	{
//		pt = new Point2D(current.GetPoint().GetX() + dx, current.GetPoint().GetY() + dy);
//		gray_it = find(gray.begin(), gray.end(), *pt);
//		black_it = find(black.begin(), black.end(), *pt);
//		if (gray_it == gray.end() && black_it == black.end()) // this is a new point
//		{
//			// very important to tunnels
//			if (maze[current.GetPoint().GetY() + dy][current.GetPoint().GetX() + dx] == ConstValue::WALL)
//				weight = wall_weight;
//			else weight = space_weight;
//			// weight depends on previous weight and wheater we had to dig
//			// to this point or not
//			tmp = new Node(*pt, target, current.GetG() + weight);
//			pq.emplace(tmp); // insert first node to priority queue
//			gray.push_back(*pt); // paint it gray
//			// add Parent
//			parents.push_back(Parent(tmp->GetPoint(), current.GetPoint(), true));
//		}
//	}
//}

//void RunAStar4Tunnels(int idx)
//{
//	Node current;
//	Node* tmp;
//	//Point2D* pt;
//	vector<Point2D>::iterator gray_it;
//	vector<Point2D>::iterator black_it;
//	bool finished = false;
//	double space_weight = 0.5, wall_weight = 0.5,weight;
//
//	while (!pq.empty() && !finished)
//	{
//		current = *pq.top();
//		pq.pop(); // remove it from pq
//
//		if (current.GetH() == 0) // the solution has been found
//		{
//			vector<Parent>::iterator itr;
//			finished = true;
//			// go back to start and change WALL to SPACE
//			itr = find(parents.begin(), parents.end(),
//				Parent(current.GetPoint(), current.GetPoint(), true));
//			
//			bool enter = true;
//			Point2D tmp_prev = itr->GetPrev();
//			Point2D tmp_cur = itr->GetCurrent();
//			while (itr->HasParent())
//			{
//				tmp_prev = itr->GetPrev();
//				tmp_cur = itr->GetCurrent();
//				// set SPACE
//				if (maze[tmp_cur.GetY()][tmp_cur.GetX()] == ConstValue::WALL)
//				{
//					maze[tmp_cur.GetY()][tmp_cur.GetX()] = ConstValue::SPACE;
//
//					if (enter)
//					{
//						// building a door
//						//all_rooms[idx].addDoor(new Point2D(tmp_cur.GetY(), tmp_cur.GetX());
//						cout << "--- " << "y: " << tmp_cur.GetY() << " x: " << tmp_cur.GetX() << endl;
//						maze[tmp_cur.GetY()][tmp_cur.GetX()] = ConstValue::AMMO;
//						enter = false;
//					}
//				}
//
//				else if (maze[tmp_cur.GetY()][tmp_cur.GetX()] != ConstValue::WALL && !enter)
//				{
//					enter = true;
//					cout << "--- " << "y: " << tmp_cur.GetY() << " x: " << tmp_cur.GetX() << endl;
//					maze[tmp_cur.GetY()][tmp_cur.GetX()] = ConstValue::AMMO;
//				}
//
//				itr = find(parents.begin(), parents.end(),
//					Parent(tmp_prev, current.GetPoint(), true));
//			}
//
//		}
//		else // check the neighbours
//		{
//			// remove current from gray 
//			gray_it = find(gray.begin(), gray.end(), current.GetPoint());
//			if (gray_it != gray.end())
//				gray.erase(gray_it);
//			// and paint it black
//			black.push_back(current.GetPoint());
//			// try to go UP
//			AddNewNode(current, UP);
//			// try to go DOWN
//			AddNewNode(current, DOWN);
//			// try to go LEFT
//			AddNewNode(current, LEFT);
//			// try to go RIGHT
//			AddNewNode(current, RIGHT);
//		}
//	} // while
//}

//void DigTunnels()
//{
//	int i, j;
//
//
//	for (i = 0; i < NUM_ROOMS; i++)
//	{
//		for (j = i + 1; j < NUM_ROOMS; j++)
//		{
//			cout << i << " " << all_rooms[i].GetCenter().GetX() << " "  << all_rooms[i].GetCenter().GetY()<< endl;
//
//			start = all_rooms[i].GetCenter();
//			target = all_rooms[j].GetCenter();
//
//			// printf("Start: %d      Target: %d\n", i, j);
//
//			Node* tmp = new Node(start, target, 0);
//			while (!pq.empty())
//				pq.pop();
//
//			pq.emplace(tmp); // insert first node to priority queue
//			gray.clear();
//			gray.push_back(start); // paint it gray
//			black.clear();
//			parents.clear();
//			parents.push_back(Parent(tmp->GetPoint(),
//				tmp->GetPoint(), false));
//			RunAStar4Tunnels(i);
//			delete tmp;
//		}
//	}
//}

//void SetupMaze()
//{
//	int i, j,counter;
//	int left, right, top, bottom;
//	bool isValidRoom;
//	Room* pr=NULL;
//
//	for (counter = 0; counter < NUM_ROOMS; counter++)
//	{
//		// create room
//		do
//		{
//			free(pr);
//			pr = new Room(Point2D(rand()%MSIZE,rand() % MSIZE),
//				Room::MINIMUM_SIZE + rand() % 15, Room::MINIMUM_SIZE + rand() % 25);
//
//			//Set limits to the room and check for leakage from window size
//			top = pr->GetCenter().GetY() - pr->GetHeight() / 2;
//			if (top < 0) top = 0;
//			bottom = pr->GetCenter().GetY() + pr->GetHeight() / 2;
//			if (bottom >= MSIZE) bottom = MSIZE - 1;
//			left = pr->GetCenter().GetX() - pr->GetWidth() / 2;
//			if (left < 0) left = 0;
//			right = pr->GetCenter().GetX() + pr->GetWidth() / 2;
//			if (right >= MSIZE) right = MSIZE - 1;
//
//			//check overlapping rooms 
//			isValidRoom = true;
//			for (i = 0; i < counter && isValidRoom; i++)
//				if (all_rooms[i].IsOverlap(*pr))
//					isValidRoom = false;
//
//		} while (!isValidRoom);
//
//		all_rooms[counter] = *pr;
//		for (i = top; i <= bottom; i++)
//			for (j = left; j <= right; j++)
//				maze[i][j] = ConstValue::SPACE;
//	}
//
//	//Create ammo storgae
//	for (i = 0; i < ConstValue::NUM_OF_AMMO_STORAGE; i++)
//	{
//		int roomIndex = i;
//		Storage *s = new Storage(all_rooms[roomIndex], TRUE);
//		ammoStorage[i] = *s;
//		drawStorage(*s);
//	}
//
//	//Create medical storgae
//	for (i = 0; i < ConstValue::NUM_OF_MEDICAL_STORAGE; i++)
//	{
//		int roomIndex = NUM_ROOMS - i - 1;
//		Storage *s = new Storage(all_rooms[roomIndex], FALSE);
//		medicalStorage[i] = *s;
//		drawStorage(*s);
//	}
//
//	DigTunnels();
//}
