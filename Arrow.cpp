#include "Arrow.h"
#include "template.h"

Arrow::Arrow(app * App, float time, int x, int y)
{
	m_AppRef = App;
	m_Sprite = agk::CreateSprite(m_AppRef->getImageDatabase()->getImage("Media\\arrow_strip10.png"));
	agk::SetSpriteOffset(m_Sprite, 16, 16);
	agk::SetSpriteAnimation(m_Sprite, 32, 32, 10);
	agk::PlaySprite(m_Sprite, 20);
	m_TimeToDie = time + 10.0f;
	m_Transform = new Transform((float)x * 64.0f, (float)y*64.0f, { 32,32 });
}

Arrow::~Arrow()
{
	delete m_Transform;
	agk::DeleteSprite(m_Sprite);
}

void Arrow::Update(float time, float delta)
{
	m_Transform->Update(delta);
	agk::SetSpritePositionByOffset(m_Sprite, m_Transform->getX(), m_Transform->getY());
	if (time > m_TimeToDie)
		m_AppRef->DestroyArrow();
}
