#include "Wagon.h"
#include "agk.h"
#include "template.h"

Wagon::Wagon(app * App, unsigned entityIndex, unsigned wagon, int x, int y) : Hireling(App, entityIndex, wagon, x, y)
{
	agk::SetSpriteImage(m_SpriteIndex, m_App->getImageDatabase()->getImage("Media\\wagon.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 208, 192, 16);
	//agk::SetSpriteSize(m_SpriteIndex, 64.0f, -1.0f);
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.33f, agk::GetSpriteHeight(m_SpriteIndex) * 0.67f);
	agk::PlaySprite(m_SpriteIndex, 8, 1, 9, 12);
	m_Type = Entity::OTHER;
}

void Wagon::Think()
{
}
