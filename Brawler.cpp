#include "Brawler.h"
#include "template.h"
#include "agk.h"

Brawler::Brawler(app * App, unsigned entityIndex, unsigned wagon, int x, int y) : Hireling(App, entityIndex, wagon, x, y)
{
	agk::SetSpriteFrame(m_SpriteIndex, 4);
	m_Type = Entity::BRAWLER;
}

void Brawler::Think()
{
	if (Hireling::GetHealth() < 0.3)
	{
		// Retreat
	}
	else
	{
		Entity * best = m_App->GetEntityManager()->GetEntity(m_Best);
		if (best == nullptr)
			best = m_App->GetEntityManager()->GetNearest(Entity::ARCHER, this, 32.0f);
		if (best != nullptr)
		{
			// Cache our best target
			m_Best = best->GetIndex();
			// Move toward Best Target
			float bestX = best->GetTransform()->getX();
			float dx = bestX - m_Transform->getX();
			float bestY = best->GetTransform()->getY();
			float dy = bestY - m_Transform->getY();
			float theta = agk::ATan2(dy, dx);
			bool validMove = false;
			int attempts = 9;
			while (!validMove && attempts-- > 0)
			{
				int newX = bestX + agk::Cos(theta);
				int newY = bestY + agk::Sin(theta);
				validMove = Hireling::Move(newX, newY);
				theta += 45.0f;
			}
		}
		else
		{
			int width = m_App->getCombatGrid()->GetWidth() - 1;
			int height = m_App->getCombatGrid()->GetHeight() - 1;
			int curX = this->GetTransform()->getX();
			int curY = this->GetTransform()->getY();
			int newX = agk::Random(curX - 5, curX + 5);
			newX = newX < 0 ? 0 : newX;
			newX = newX > width ? width : newX;
			int newY = agk::Random(curY - 5, curY + 5);
			newY = newY < 0 ? 0 : newY;
			newY = newY > width ? width : newY;
			Hireling::Move(newX, newY);
		}
	}
}

void Brawler::Attack()
{
	Entity * nearest = m_App->GetEntityManager()->GetEntity(m_Nearest);
	if (nearest == nullptr)
		nearest = m_App->GetEntityManager()->GetNearest(Entity::ARCHER, this, 1.0f);
	/*if (best != nullptr)
	{
	// Cache our best target
	m_Best = best->GetIndex();

	m_App->GetEntityManager()->NewArrow(m_Transform->getX(),
	m_Transform->getY(),
	m_Best);
	m_NextAttack = agk::Timer() + 3.0f;
	}*/
	if (nearest != nullptr)
	{
		// Cache our nearest target
		m_Nearest = nearest->GetIndex();
		Hireling * target = (Hireling*)nearest;
		m_App->GetEntityManager()->NewHitEffect(target->GetTransform()->getX(), target->GetTransform()->getY());
		target->Damage(1);
		m_NextAttack = agk::Timer() + 1.0f;
	}
}
