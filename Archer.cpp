#include "Archer.h"
#include "template.h"
#include "agk.h"

Archer::Archer(app * App, unsigned entityIndex, int x, int y) : Character(App, entityIndex, x, y)
{
	agk::SetSpriteFrame(m_SpriteIndex, 1);
	m_Type = Entity::ARCHER;
}

void Archer::Think()
{
	app * AppRef = Entity::GetAppRef();
	if (Character::GetHealth() < 0.3)
	{
		// Retreat
	}
	else
	{
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
			m_App->GetEntityManager()->FindNearest(Entity::ARCHER, m_EntityIndex));
	}
	
}
