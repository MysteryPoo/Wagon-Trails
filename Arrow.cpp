#include "Arrow.h"
#include "template.h"

Arrow::Arrow(app * App, unsigned entityIndex, float time, int x, int y) : Entity(App, entityIndex, x, y)
{
	m_SpriteIndex = agk::CreateSprite(m_AppRef->getImageDatabase()->getImage("Media\\arrow_strip10.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);
	m_TimeToDie = time + 10.0f;
	m_Transform = new Transform((float)x * 64.0f, (float)y * 64.0f, { 32,32 });
}

Arrow::~Arrow()
{
	delete m_Transform;
	agk::DeleteSprite(m_SpriteIndex);
}

void Arrow::Update(float time, float delta)
{
	Entity::Update(time, delta);
	if (time > m_TimeToDie)
		m_AppRef->GetEntityManager()->GetEntity(m_EntityIndex)->TimeToDie(true);
}

void Arrow::Move(int x, int y)
{
	agk::SetSpriteAngle(m_SpriteIndex, agk::ATan2(y, x));
	m_Transform->Move(x, y);
}
