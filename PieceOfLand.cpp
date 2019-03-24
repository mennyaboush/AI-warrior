#include "PieceOfLand.h"

PieceOfLand::PieceOfLand()
{
}

PieceOfLand::~PieceOfLand()
{
}

PieceOfLand::PieceOfLand(Point2D & location, int type, double saftyScore) :location(&location), type(type), saftyScore(saftyScore)
{
}

