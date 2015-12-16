#include "Arrow.h"
#include "template.h"

Arrow::Arrow(app * App, unsigned entityIndex, float time, unsigned targetIndex, int x, int y) : Entity(App, entityIndex, x, y)
{
	m_SpriteIndex = agk::CreateSprite(m_App->getImageDatabase()->getImage("Media\\arrow_strip10.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);
	m_TimeToDie = time + 5.0f;
	m_Transform = new Transform((float)x * 64.0f, (float)y * 64.0f, { 64,64 }, 500.0f);
	m_TargetIndex = targetIndex;
	m_Hit = false;
}

Arrow::~Arrow()
{
	delete m_Transform;
	agk::DeleteSprite(m_SpriteIndex);
}

void Arrow::Update(float time, float delta)
{
	Entity::Update(time, delta);
	Entity* entity = m_App->GetEntityManager()->GetEntity(m_TargetIndex);
	int goalX = entity->GetTransform()->getX();
	int goalY = entity->GetTransform()->getY();
	if (entity != nullptr)
	{
		Move(goalX, goalY);
	}
	if (!m_Hit && agk::GetSpriteCollision(entity->GetSprite(), m_SpriteIndex))
	{
		m_TimeToDie = time + 0.2f;
		m_Hit = true;
	}
	if (time > m_TimeToDie)
		m_App->GetEntityManager()->GetEntity(m_EntityIndex)->TimeToDie(true);
}

void Arrow::Move(int x, int y)
{
	agk::SetSpriteAngle(m_SpriteIndex, m_Transform->getDirection());
	m_Transform->Move(x, y);
}
