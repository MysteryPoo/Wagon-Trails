#include "Transform.h"
#include <agk.h>

Transform::Transform(float x, float y, SpriteSize spriteSize)
{
	this->m_SpriteX = x;
	this->m_SpriteY = y;
	this->m_Direction = 0;
	this->m_Speed = 0;
	this->m_GoalX = x / spriteSize.Width;
	this->m_GoalY = y / spriteSize.Height;
	this->m_SpriteSize.Width = spriteSize.Width;
	this->m_SpriteSize.Height = spriteSize.Height;
}

void Transform::Move(int x, int y)
{
	m_GoalX = x;
	m_GoalY = y;
}

void Transform::setDirection(float direction)
{
	this->m_Direction = direction;
}

void Transform::setSpeed(float speed)
{
	this->m_Speed = speed;
}

void Transform::Update(float time)
{
	float dx = m_GoalX * m_SpriteSize.Width - m_SpriteX;
	float dy = m_GoalY * m_SpriteSize.Height - m_SpriteY;
	float distance = agk::Sqrt(dx*dx + dy*dy);
	if (distance < 1.1f)
	{
		m_Speed = 0;
		m_SpriteX = m_GoalX * m_SpriteSize.Width;
		m_SpriteY = m_GoalY * m_SpriteSize.Height;
	}
	else
	{
		m_Direction = agk::ATan2(dy, dx);
		m_Speed = 200.0f;
		m_SpriteX += m_Speed * time * agk::Cos(m_Direction);
		m_SpriteY += m_Speed * time * agk::Sin(m_Direction);
	}
}
