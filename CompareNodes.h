#pragma once
#include "Node.h"
#include "Maze.h"

class CompareNodes
{
public:
	CompareNodes();
	~CompareNodes();
	bool operator ( ) (const Node* n1, const Node* n2);
};

