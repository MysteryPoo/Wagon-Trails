#include "Entity.h"
#include "template.h"

Entity::Entity(app * App)
{
	m_AppRef = App;
	ImageDatabase *id = m_AppRef->getImageDatabase();
	m_SpriteIndex = agk::CreateSprite(id->getImage("Media\\Humanoids1.png"));
	agk::SetSpriteOffset(m_SpriteIndex, agk::GetSpriteWidth(m_SpriteIndex) * 0.5f, agk::GetSpriteHeight(m_SpriteIndex) * 0.5f);
	//float x = (float)agk::Random(0, agk::GetVirtualWidth());
	//float y = (float)agk::Random(0, agk::GetVirtualHeight());
	//float direction = (float)agk::Random(0, 360);
	//float speed = (float)agk::Random(10, 50);
	m_Position = new Transform(0.0f, 0.0f);
	//agk::SetSpritePositionByOffset(m_SpriteIndex, x, y);
}

Entity::~Entity()
{
	delete m_Position;
	agk::DeleteSprite(m_SpriteIndex);
}

void Entity::Update(float delta)
{
	m_Position->Update(delta);
	agk::SetSpritePositionByOffset(m_SpriteIndex, m_Position->getX(), m_Position->getY());
}
