#pragma once
#include <fstream>
#include "Room.h"
#include "Door.h"

using namespace std;

class Maze
{
public:
	static const int MSIZE = 100;
	static const int SPACE = 1;
	static const int WALL = 2;
	static const int VISITED = 3;
	static const int START = 4;
	static const int TARGET = 5;
	static const int GRAY = 6;
	static const int MEDICAL = 7;
	static const int AMMO = 8;
	static const int WARRIOR = 9;
	static const int DOOR = 10;
	static const int NUM_ROOMS = 10;

private:
	static Maze* maze;
	int parts[MSIZE][MSIZE];
	Room all_rooms[NUM_ROOMS];

	Maze();

public:
	~Maze();

	Maze& getInstance();
	
	void loadMazeFromFile();
	void cleanUp();
	void drawType(int type);
	
	int** getParts() const;

};
