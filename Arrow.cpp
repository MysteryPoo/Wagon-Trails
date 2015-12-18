#include "Arrow.h"
#include "template.h"
#include "Character.h"

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
	m_Type = Entity::ARROW;
}

Arrow::~Arrow()
{
	m_App->GetEntityManager()->NewHitEffect(m_Transform->getX(), m_Transform->getY());
	Character * entity = (Character*)m_App->GetEntityManager()->GetEntity(m_TargetIndex);
	if(entity != nullptr)
		entity->Damage(1);
}

void Arrow::Update(float time, float delta)
{
	Entity::Update(time, delta);
	Entity* entity = m_App->GetEntityManager()->GetEntity(m_TargetIndex);
	if (entity != nullptr)
	{
		int goalX = entity->GetTransform()->getX();
		int goalY = entity->GetTransform()->getY();
		Move(goalX, goalY);
		if (!m_Hit && agk::GetSpriteCollision(entity->GetSprite(), m_SpriteIndex))
		{
			m_TimeToDie = time + 0.2f;
			m_Hit = true;
		}
	}
	else
		Entity::TimeToDie(true);
	if (time > m_TimeToDie)
		Entity::TimeToDie(true);
}

void Arrow::Move(int x, int y)
{
	agk::SetSpriteAngle(m_SpriteIndex, m_Transform->getDirection());
	m_Transform->Move(x, y);
}
