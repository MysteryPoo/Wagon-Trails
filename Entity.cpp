#include "Entity.h"
#include "template.h"

Entity::Entity(app * App, unsigned entityIndex, int x, int y)
{
	m_AppRef = App;
	m_EntityIndex = entityIndex;
	m_TimeToDie = false;
}

Entity::~Entity()
{
	delete m_Transform;
	agk::DeleteSprite(m_SpriteIndex);
}

void Entity::Update(float timer, float delta)
{
	// Move the transform
	m_Transform->Update(delta);
	// Update the sprite
	agk::SetSpritePositionByOffset(m_SpriteIndex, m_Transform->getSpriteX(), m_Transform->getSpriteY());
}
