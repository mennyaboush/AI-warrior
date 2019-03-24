#include "Maze.h"

Maze* Maze::maze = nullptr;

Maze::Maze()
{
	//MazePart(*parts)[MSIZE] = new MazePart[MSIZE][MSIZE];

	for (int i = 0; i < MSIZE; i++)
	{
		for (int j = 0; j < MSIZE; j++)
		{
			parts[i][j] = *new MazePart(new Point2D(j, i));
			parts[i][j].setLocation(*new Point2D(j, i));
		}
	}

	loadMazeFromFile();
}

Maze::~Maze()
{
	delete maze;
}

Maze& Maze::getInstance()
{
	if (maze == nullptr)
	{
		maze = new Maze();
	}
	return *maze;
}

void Maze::loadMazeFromFile()
{
	ifstream file;

	// 1. load maze stracture
	file.open("maze.txt");
	int col, row, type;
	file >> col;
	file >> row;
	for (int i = 0; i < MSIZE; i++)
	{
		for (int j = 0; j < MSIZE; j++)
		{
			file >> type;
			parts[i][j].setType(type);
		}
	}
	file.close();

	// 2. load rooms 
	file.open("rooms.txt");
	int size, x, y, h, w;
	file >> size;
	for (int i = 0; i < NUM_ROOMS; i++)
	{
		file >> x;
		file >> y;
		file >> h;
		file >> w;
		int idx = i + 1;
		all_rooms[i] = *new Room(idx, *new Point2D(x, y), w, h);
	}
	file.close();

	// 3. load doors
	file.open("doors2.txt");
	int from, x1, y1, x2, y2, rooms_num;
	file >> size;

	// sourceRoom ,enter and exit location of the doors, vactor of destionations
	for (int i = 0; i < size; i++)
	{
		file >> from;
		file >> x1;
		file >> y1;
		file >> x2;
		file >> y2;
		file >> rooms_num;
		Door* door = new Door(all_rooms[from - 1], *new Point2D(x1, y1), *new Point2D(x2, y2));

		for (int j = 0; j < rooms_num; j++) {
			int roomIndex;
			file >> roomIndex;
			door->addDestination(all_rooms[roomIndex - 1]);
		}
		all_rooms[from - 1].addDoor(*door);
	}
	file.close();
}

//void Maze::cleanUp()
//{
//	// clean up the maze
//	for (int i = 0; i < MSIZE; i++)
//	{
//		for (int j = 0; j < MSIZE; j++)
//			parts[i][j].setType(MazePart::WALL);
//	}
//}

Room* Maze::getRooms() const
{
	return (Room*)all_rooms;
}

MazePart** Maze::getParts() const
{
	return (MazePart**)parts;
}

double Maze::getSaftyScore(Point2D &point) const
{
	return parts[point.GetY()][point.GetX()].getSaftyScore();
}

bool Maze::isPointInRoom(Point2D &point) const
{
	// get room of the point and check
	return true;
}
