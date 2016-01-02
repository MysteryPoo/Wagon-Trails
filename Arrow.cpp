#include "Arrow.h"
#include "template.h"
#include "Hireling.h"

Arrow::Arrow(app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y) : Attack(App, entityIndex, timeToDie, sourceIndex, targetIndex, x, y)
{
	m_SpriteIndex = agk::CreateSprite(m_App->getImageDatabase()->getImage("Media\\arrow_strip10.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);
}
