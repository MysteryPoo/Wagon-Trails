#include "CombatGrid.h"
#include "agk.h"
#include "template.h"

CombatGrid::CombatGrid(app * App, int Width, int Height)
{
	m_App = App;
	ImageDatabase * id = m_App->getImageDatabase();
	totalCost = 0;
	m_Width = Width;
	m_Height = Height;
	m_Pather = new MicroPather(this);
	m_Grid = new char[Width*Height + 1]();
	m_Sprites = new std::vector<int>();

	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			int rand = agk::Random(0, 100);
			if (rand > 70 || x == 0 || x == m_Width - 1 || y == 0 || y == m_Height - 1)
			{
				m_Grid[y*Width + x] = CombatGrid::OBSTACLE;
				int Sprite = agk::CreateSprite(id->getImage("Media\\TerrainTiles.png"));
				agk::SetSpriteSnap(Sprite, 1);
				agk::SetSpriteAnimation(Sprite, 64, 64, 64);
				agk::SetSpriteFrame(Sprite, agk::Random(0, 100) > 50 ? 1 : 2);
				agk::SetSpriteOffset(Sprite, agk::GetSpriteWidth(Sprite) * 0.5f, agk::GetSpriteHeight(Sprite) * 0.5f);
				agk::SetSpritePositionByOffset(Sprite, (float)x * 64.0f, (float)y * 64.0f);
				agk::SetSpriteDepth(Sprite, 51);
				m_Sprites->push_back(Sprite);
				Sprite = agk::CreateSprite(id->getImage("Media\\TerrainTiles2.png"));
				agk::SetSpriteSnap(Sprite, 1);
				agk::SetSpriteAnimation(Sprite, 64, 64, 64);
				agk::SetSpriteFrame(Sprite, agk::Random(0, 100) > 50 ? 32 : 40);
				agk::SetSpriteOffset(Sprite, agk::GetSpriteWidth(Sprite) * 0.5f, agk::GetSpriteHeight(Sprite) * 0.5f);
				agk::SetSpritePositionByOffset(Sprite, (float)x * 64, (float)y * 64);
				agk::SetSpriteDepth(Sprite, 50);
				m_Sprites->push_back(Sprite);
			}
			else
			{
				m_Grid[y*Width + x] = CombatGrid::OPEN;
				int Sprite = agk::CreateSprite(id->getImage("Media\\TerrainTiles.png"));
				agk::SetSpriteSnap(Sprite, 1);
				agk::SetSpriteAnimation(Sprite, 64, 64, 64);
				agk::SetSpriteFrame(Sprite, agk::Random(0, 100) > 50 ? 1 : 2);
				agk::SetSpriteOffset(Sprite, agk::GetSpriteWidth(Sprite) * 0.5f, agk::GetSpriteHeight(Sprite) * 0.5f);
				agk::SetSpritePositionByOffset(Sprite, (float)x * 64, (float)y * 64);
				agk::SetSpriteDepth(Sprite, 51);
				m_Sprites->push_back(Sprite);
			}
		}
	}
}

CombatGrid::~CombatGrid()
{
	delete m_Pather;
	delete m_Grid;
	for (std::vector<int>::iterator it = m_Sprites->begin(); it != m_Sprites->end(); ++it)
	{
		agk::DeleteSprite(*it);
	}
	delete m_Sprites;
}

CombatGrid::Point * CombatGrid::NodeToXY(void * node)
{
	intptr_t index = (intptr_t)node;
	CombatGrid::Point * point = new Point();
	point->y = index / m_Width;
	point->x = index - point->y * m_Width;
	return point;
}

void CombatGrid::NodeToXY(void * node, int * x, int * y)
{
	intptr_t index = (intptr_t)node;
	*y = index / m_Width;
	*x = index - *y * m_Width;
}

void * CombatGrid::XYToNode(int x, int y)
{
	return (void*)(y*m_Width + x);
}

bool CombatGrid::Passable(int x, int y)
{
	if (m_Grid[y*m_Width + x] == CombatGrid::OBSTACLE || m_App->GetEntityManager()->EntityAt(x, y))
		return false;
	else
		return true;
}

float CombatGrid::LeastCostEstimate(void * nodeStart, void * nodeEnd)
{
	Point * Start, *End;
	Start = NodeToXY(nodeStart);
	End = NodeToXY(nodeEnd);

	/* Compute the minimum path cost using distance measurement. It is possible
	to compute the exact minimum path using the fact that you can move only
	on a straight line or on a diagonal, and this will yield a better result.
	*/
	int dx = End->x - Start->x;
	int dy = End->y - Start->y;
	delete Start;
	delete End;
	return (float)agk::Sqrt((float)(dx*dx) + (float)(dy*dy));
}

void CombatGrid::AdjacentCost(void * node, micropather::MPVector<StateCost>* neighbors)
{
	Point * Node = NodeToXY(node);
	int x = Node->x, y = Node->y;
	const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };

	for (int i = 0; i<8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		bool pass = Passable(nx, ny);
		if (pass)
		{
			// Normal floor
			StateCost nodeCost = { XYToNode(nx, ny), cost[i] };
			neighbors->push_back(nodeCost);
		}
		else
		{
			// Normal floor
			StateCost nodeCost = { XYToNode(nx, ny), FLT_MAX };
			neighbors->push_back(nodeCost);
		}
	}
}

void CombatGrid::PrintStateInfo(void * state)
{
}
