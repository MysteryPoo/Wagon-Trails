#include "Archer.h"
#include "template.h"
#include "agk.h"

Archer::Archer(app * App) : Entity(App)
{

}

Archer::Archer(app * App, int x, int y) : Entity(App, x, y)
{

}

void Archer::Think()
{
	app * AppRef = Entity::GetAppRef();
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
	Entity::Move(newX, newY);
}
