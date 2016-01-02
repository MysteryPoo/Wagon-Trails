#include "Hireling.h"
#include "ImageDatabase.h"
#include "template.h"

Hireling::Hireling(class app * App, unsigned entityIndex, unsigned wagon, int x, int y) : Entity(App, entityIndex, x, y)
{
	ImageDatabase *id = m_App->getImageDatabase();
	m_SpriteIndex = agk::CreateSprite(id->getImage("Media\\Humanoids1.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 64, 64, 64);
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.5f, agk::GetSpriteHeight(m_SpriteIndex) * 0.5f);
	m_NextThought = m_NextAttack = 0.0f;
	m_Health = m_HealthMax = 10;
	m_Best = m_Nearest = 0;
	m_Wagon = wagon;
}

void Hireling::Damage(int damage)
{
	m_Health -= damage;
}

void Hireling::Update(float time, float delta)
{
	Entity::Update(time, delta);
	// Move to next node in path
	if (m_NodeIndex < m_Path.size() && m_Transform->getSpeed() == 0.0f)
	{
		int x, y;
		m_App->getCombatGrid()->NodeToXY(m_Path[m_NodeIndex++], &x, &y);
		if (m_App->getCombatGrid()->Passable(x, y))
		{
			m_Transform->Move(x, y);
		}
		else
		{
			m_App->getCombatGrid()->NodeToXY(m_Path[m_Path.size() - 1], &x, &y);
			Move(x, y);
		}
	}
	// Draw the path
	for (unsigned n = 0; n < m_Path.size(); ++n)
	{
		int x, y;
		m_App->getCombatGrid()->NodeToXY(m_Path[n], &x, &y);
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
	// Attack
	if (time > m_NextAttack)
	{
		this->Attack();
	}
	// Check Health
	if (m_Health < 0)
	{
		Entity::TimeToDie(true);
	}
}

bool Hireling::Move(int x, int y)
{
	if (m_App->getCombatGrid()->Passable(x, y))
	{
		float totalCost;
		void * start = m_App->getCombatGrid()->XYToNode(m_Transform->getX(), m_Transform->getY());
		void * end = m_App->getCombatGrid()->XYToNode(x, y);
		int result = m_App->getCombatGrid()->GetPather()->Solve(start, end, &m_Path, &totalCost);
		m_NodeIndex = 1;
		return true;
	}
	return false;
}
