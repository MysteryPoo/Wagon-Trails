#pragma once

class Transform
{
	float m_SpriteX, m_SpriteY, m_Direction, m_Speed;
	int m_GoalX, m_GoalY;
	struct SpriteSize
	{
		int Width, Height;
	} m_SpriteSize;
	void setDirection(float direction);
	void setSpeed(float speed);
public:
	Transform(float x = 0.0f, float y = 0.0f, SpriteSize spriteSize = { 64,64 });
	void Move(int x, int y);
	float getDirection() { return m_Direction; }
	float getSpeed() { return m_Speed; }
	float getSpriteX() { return m_SpriteX; }
	float getSpriteY() { return m_SpriteY; }
	int getX() { return m_GoalX; };
	int getY() { return m_GoalY; };
	void Update(float time);
};