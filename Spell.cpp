#include "Spell.h"
#include "template.h"
#include "Hireling.h"

Spell::Spell(app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y) : Attack(App, entityIndex, timeToDie, sourceIndex, targetIndex, x, y)
{
	m_SpriteIndex = agk::CreateSprite(m_App->getImageDatabase()->getImage("Media\\spell.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);
}
