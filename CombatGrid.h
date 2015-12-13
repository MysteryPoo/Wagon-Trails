#pragma once

#include "micropather.h"
#include <vector>

using namespace micropather;

class CombatGrid : public Graph
{
	class app * m_AppRef;
	//MPVector<void*> m_Path;
	float totalCost;
	MicroPather * m_Pather;
	int m_Width, m_Height;
	char* m_Grid;
	enum Tile
	{
		OPEN = 0,
		OBSTACLE = 1,
		ELEVATED = 2,
		CHOKE = 4
	};
	struct Point
	{
		int x, y;
	};
	std::vector<int> * m_Sprites;
public:
	CombatGrid(class app * App, int Width = 20, int Height = 20);
	~CombatGrid();
	int GetWidth() { return m_Width; };
	int GetHeight() { return m_Height; };
	Point * NodeToXY(void * node);
	void NodeToXY(void * node, int * x, int * y);
	void * XYToNode(int x, int y);
	bool Passable(int x, int y);
	virtual float LeastCostEstimate(void* nodeStart, void* nodeEnd);
	virtual void AdjacentCost(void* node, micropather::MPVector<StateCost> *neighbors);
	virtual void PrintStateInfo(void * state);
	MicroPather * Pather() { return m_Pather; };
};