#include "Wagon.h"
#include "agk.h"
#include "template.h"

Wagon::Wagon(app * App, unsigned entityIndex, int x, int y) : Character(App, entityIndex, x, y)
{
	agk::SetSpriteImage(m_SpriteIndex, m_App->getImageDatabase()->getImage("Media\\wagon.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 208, 192, 16);
	agk::SetSpriteSize(m_SpriteIndex, 64.0f, -1.0f);
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.5f, agk::GetSpriteHeight(m_SpriteIndex) * 0.5f);
	agk::SetSpriteFrame(m_SpriteIndex, 1);
	m_Type = Entity::OTHER;
}

void Wagon::Think()
{
}
