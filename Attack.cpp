#include "Attack.h"
#include "template.h"
#include "Hireling.h"

Attack::Attack(app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y) : Entity(App, entityIndex, x, y)
{
	/*m_SpriteIndex = agk::CreateSprite(m_App->getImageDatabase()->getImage("Media\\arrow_strip10.png"));
	agk::SetSpriteAnimation(m_SpriteIndex, 32, 32, 10);
	agk::SetSpriteOffset(m_SpriteIndex, 16, 16);
	agk::PlaySprite(m_SpriteIndex, 20);*/
	m_TimeToDie = timeToDie + 5.0f;
	m_Transform = new Transform(x, y, { 64,64 }, 500.0f);
	m_SourceIndex = sourceIndex;
	m_TargetIndex = targetIndex;
	m_Hit = false;
	m_Type = Entity::ATTACK;
}

Attack::~Attack()
{
	m_App->GetEntityManager()->NewHitEffect(m_Transform->getX(), m_Transform->getY());
	Hireling * entity = (Hireling*)m_App->GetEntityManager()->GetEntity(m_TargetIndex);
	if (entity != nullptr)
		entity->Damage(1);
}

void Attack::Update(float time, float delta)
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

bool Attack::Move(int x, int y)
{
	agk::SetSpriteAngle(m_SpriteIndex, m_Transform->getDirection());
	m_Transform->Move(x, y);
	return true;
}
