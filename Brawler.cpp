#include "Brawler.h"
#include "template.h"
#include "agk.h"

Brawler::Brawler(app * App, unsigned entityIndex, int x, int y) : Character(App, entityIndex, x, y)
{
	// No special instructions for the Archer ctr. Simply calls Character ctr.
	agk::SetSpriteFrame(m_SpriteIndex, 4);
	m_Type = Entity::BRAWLER;
}

void Brawler::Think()
{
	app * AppRef = Entity::GetAppRef();
	if (Character::GetHealth() < 0.3)
	{
		// Retreat
	}
	else
	{
		bool validTarget = false;
		// Find nearest of each type of enemy
		bool goArcher = false;
		float distArcher;
		unsigned nearestArcher = m_App->GetEntityManager()->FindNearest(Entity::ARCHER, m_EntityIndex, &distArcher);
		bool goBrawler = false;
		float distBrawler;
		unsigned nearestBrawler = m_App->GetEntityManager()->FindNearest(Entity::BRAWLER, m_EntityIndex, &distBrawler);
		bool goMage = false;
		float distMage;
		unsigned nearestMage = m_App->GetEntityManager()->FindNearest(Entity::MAGE, m_EntityIndex, &distMage);
		// Validate targets
		if (m_App->GetEntityManager()->GetEntity(nearestBrawler)->GetType() == Entity::BRAWLER)
			goBrawler = true;
		if (m_App->GetEntityManager()->GetEntity(nearestArcher)->GetType() == Entity::ARCHER)
			goArcher = true;
		if (m_App->GetEntityManager()->GetEntity(nearestMage)->GetType() == Entity::MAGE)
			goMage = true;
		// Select Best target
		unsigned bestTarget;
		if (goArcher)
			bestTarget = nearestArcher;
		else if (goBrawler)
			bestTarget = nearestBrawler;
		else if (goMage)
			bestTarget = nearestMage;
		validTarget = goBrawler | goArcher | goMage;
		// Select nearest target
		unsigned nearestTarget;
		float minDistance = min(distBrawler, min(distArcher, distMage));
		if (goBrawler && minDistance == distBrawler)
			nearestTarget = nearestBrawler;
		else if (goArcher && minDistance == distArcher)
			nearestTarget = nearestArcher;
		else if (goMage && minDistance == distMage)
			nearestTarget = nearestMage;
		else
			nearestTarget = bestTarget;
		// One of the targets is valid otherwise there is no tactical maneuver. Move as "Idle"
		if (validTarget)
		{
			// Within Range of Best Target
			if (m_App->GetEntityManager()->GetDistance(m_EntityIndex, bestTarget) <= 1.5f)
			{
				// Attack Best Target
				m_App->GetEntityManager()->NewArrow(m_Transform->getX(),
					m_Transform->getY(),
					bestTarget);
				// Move toward advantageous position

				// Keep at distance
				// Move toward Best Target
				float dx = m_App->GetEntityManager()->GetEntity(bestTarget)->GetTransform()->getX() - m_Transform->getX();
				float dy = m_App->GetEntityManager()->GetEntity(bestTarget)->GetTransform()->getY() - m_Transform->getY();
				float theta = agk::ATan2(dy, dx);
				int newX = m_Transform->getX() + 1 * agk::Cos(theta);
				int newY = m_Transform->getY() + 1 * agk::Sin(theta);
				bool validMove = false;
				while (!validMove)
				{
					validMove = Character::Move(newX--, newY--);
				}
			}
			else // Not within Range of Best Target
			{
				if (m_App->GetEntityManager()->GetDistance(m_EntityIndex, nearestTarget) <= 1.5f)
					// Attack Nearest Target, if able
					m_App->GetEntityManager()->NewSpell(m_Transform->getX(),
						m_Transform->getY(),
						nearestTarget);
				// Move toward Best Target
				float dx = m_App->GetEntityManager()->GetEntity(bestTarget)->GetTransform()->getX() - m_Transform->getX();
				float dy = m_App->GetEntityManager()->GetEntity(bestTarget)->GetTransform()->getY() - m_Transform->getY();
				float theta = agk::ATan2(dy, dx);
				int newX = m_Transform->getX() + 1 * agk::Cos(theta);
				int newY = m_Transform->getY() + 1 * agk::Sin(theta);
				bool validMove = false;
				while (!validMove)
				{
					validMove = Character::Move(newX--, newY--);
				}
			}
		}

		// Otherwise, move randomly
		/*
		int width = AppRef->getCombatGrid()->GetWidth() - 1;
		int height = AppRef->getCombatGrid()->GetHeight() - 1;
		int curX = this->GetTransform()->getX();
		int curY = this->GetTransform()->getY();
		int newX = agk::Random(curX - 5, curX + 5);
		newX = newX < 0 ? 0 : newX;
		newX = newX > width ? width : newX;
		int newY = agk::Random(curY - 5, curY + 5);
		newY = newY < 0 ? 0 : newY;
		newY = newY > width ? width : newY;
		Character::Move(newX, newY);
		m_App->GetEntityManager()->NewArrow(m_Transform->getX(),
		m_Transform->getY(),
		m_App->GetEntityManager()->FindNearest(Entity::ARCHER, m_EntityIndex));*/
	}

}