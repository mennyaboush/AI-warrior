#pragma once
#include <fstream>
#include "Room.h"
#include "Door.h"
#include "Storage.h"
#include "MazePart.h"

using namespace std;

class Maze
{
public:
	static const int MSIZE = 100;
	static const int START = 4;
	static const int NUM_ROOMS = 10;
	static const int NUM_OF_MEDICAL_STORAGE = 2;
	static const int NUM_OF_AMMO_STORAGE = 2;
	MazePart parts[MSIZE][MSIZE];

private:
	static Maze* maze;

	Room all_rooms[NUM_ROOMS];
	Storage medicalStorage[NUM_OF_MEDICAL_STORAGE];
	Storage ammoStorage[NUM_OF_AMMO_STORAGE];

	Maze();

public:
	~Maze();
	Maze(Maze &other) = delete;
	Maze& operator=(Maze &other) = delete;
	static Maze& getInstance();
	
	void loadMazeFromFile();
	void cleanUp();
	
	MazePart** getParts() const;
	Room* getRooms() const;
	double getSaftyScore(Point2D &point) const;
	bool isPointInRoom(Point2D &point) const;

	// astar stack
	// is in room
};

