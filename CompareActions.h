#pragma once

class Action;

class CompareActions
{
public:
	CompareActions();
	~CompareActions();
	bool operator( ) (const Action* a1, const Action* a2);
};

