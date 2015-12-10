#pragma once

class Transform
{
	float x, y, direction, speed;
public:
	Transform(float x = 0.0f, float y = 0.0f, float direction = 0.0f, float speed = 0.0f);
	void Rotate(float direction);
	float getDirection() { return direction; }
	void setSpeed(float speed);
	float getSpeed() { return speed; }
	float getX() { return x; }
	float getY() { return y; }
	void Update(float time);
};