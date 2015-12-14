#include "Character.h"
#include "ImageDatabase.h"
#include "template.h"

Character::Character(class app * App, int x, int y) : Entity(App, x, y)
{
	ImageDatabase *id = m_AppRef->getImageDatabase();
	m_SpriteIndex = agk::CreateSprite(id->getImage("Media\\Humanoids1.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 64, 64, 64);
	agk::SetSpriteFrame(m_SpriteIndex, agk::Random(1, 64));
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.5f, agk::GetSpriteHeight(m_SpriteIndex) * 0.5f);
	m_Transform = new Transform((float)x * 64.0f, (float)y * 64.0f);
	m_NextThought = 0.0f;
	m_Health = m_HealthMax = 10;
}

void Character::Update(float time, float delta)
{
	Entity::Update(time, delta);
	// Move to next node in path
	if (m_NodeIndex < m_Path.size() && m_Transform->getSpeed() == 0.0f)
	{
		int x, y;
		m_AppRef->getCombatGrid()->NodeToXY(m_Path[m_NodeIndex++], &x, &y);
		if (m_AppRef->getCombatGrid()->Passable(x, y))
		{
			m_Transform->Move(x, y);
		}
		else
		{
			m_AppRef->getCombatGrid()->NodeToXY(m_Path[m_Path.size() - 1], &x, &y);
			Move(x, y);
		}
	}
	// Draw the path
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
	// Think
	if (time > m_NextThought)
	{
		m_NextThought += (float)agk::Random(30, 80) / 10.0f;
		this->Think();
	}
}

void Character::Move(int x, int y)
{
	if (m_AppRef->getCombatGrid()->Passable(x, y))
	{
		// Issue: This destroys the pathing cache, however, the cache becomes
		// corrupted because entities move and they cause collisions.
		m_AppRef->getCombatGrid()->GetPather()->Reset();
		float totalCost;
		void * start = m_AppRef->getCombatGrid()->XYToNode(m_Transform->getX(), m_Transform->getY());
		void * end = m_AppRef->getCombatGrid()->XYToNode(x, y);
		int result = m_AppRef->getCombatGrid()->GetPather()->Solve(start, end, &m_Path, &totalCost);
		m_NodeIndex = 1;
	}
}
