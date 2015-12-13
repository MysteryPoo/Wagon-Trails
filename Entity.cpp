#include "Entity.h"
#include "template.h"

void Entity::ClearPath()
{
	m_Path.resize(0);
}

Entity::Entity(app * App)
{
	m_AppRef = App;
	ImageDatabase *id = m_AppRef->getImageDatabase();
	m_SpriteIndex = agk::CreateSprite(id->getImage("Media\\Humanoids1.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 64, 64, 64);
	agk::PlaySprite(m_SpriteIndex, 5);
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.5f, agk::GetSpriteHeight(m_SpriteIndex) * 0.5f);
	m_Transform = new Transform(0.0f, 0.0f);
}

Entity::~Entity()
{
	delete m_Transform;
	agk::DeleteSprite(m_SpriteIndex);
}

void Entity::Update(float delta)
{
	if (m_NodeIndex < m_Path.size() && m_Transform->getSpeed() == 0.0f)
	{
		int x, y;
		m_AppRef->getCombatGrid()->NodeToXY(m_Path[m_NodeIndex++], &x, &y);
		m_Transform->Move(x, y);
	}
	
	for (unsigned n = 0; n < m_Path.size(); ++n)
	{
		int x, y;
		m_AppRef->getCombatGrid()->NodeToXY(m_Path[n], &x, &y);
		float drawX, drawY;
		drawX = agk::WorldToScreenX(x * 64.0f);
		drawY = agk::WorldToScreenY(y * 64.0f);
		int red = agk::MakeColor(255, 50, 50);
		int green = agk::MakeColor(50, 255, 50);
		if (n >= m_NodeIndex)
			agk::DrawEllipse(drawX, drawY, 32, 32, red, red, 0);
		else
			agk::DrawEllipse(drawX, drawY, 32, 32, green, green, 0);
	}

	m_Transform->Update(delta);
	agk::SetSpritePositionByOffset(m_SpriteIndex, m_Transform->getSpriteX(), m_Transform->getSpriteY());
}

void Entity::Move(int x, int y)
{
	if (m_AppRef->getCombatGrid()->Passable(x, y))
	{
		float totalCost;
		void * start = m_AppRef->getCombatGrid()->XYToNode(m_Transform->getX(), m_Transform->getY());
		void * end = m_AppRef->getCombatGrid()->XYToNode(x, y);
		int result = m_AppRef->getCombatGrid()->Pather()->Solve(start, end, &m_Path, &totalCost);
		m_NodeIndex = 0;
	}
}
