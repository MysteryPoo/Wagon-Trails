#include "Effect.h"
#include "template.h"

Effect::Effect(app * App, unsigned entityIndex, float time, int x, int y) : Entity(App, entityIndex, x, y)
{
	m_SpriteIndex = agk::CreateSprite(m_App->getImageDatabase()->getImage("Media\\slimehit_strip12.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);
	m_TimeToDie = time + 0.5f;
	m_Transform = new Transform(x, y, { 64,64 }, 0.0f);
	m_Type = Entity::OTHER;
}

void Effect::Update(float time, float delta)
{
	Entity::Update(time, delta);
	if (time > m_TimeToDie)
		Entity::TimeToDie(true);
}

bool Effect::Move(int x, int y)
{
	return true;
}
