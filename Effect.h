#pragma once

#include "agk.h"
#include "Transform.h"
#include "Entity.h"

class Effect : public Entity
{
	float m_TimeToDie;
public:
	Effect(class app * App, unsigned entityIndex, float time, int x, int y);
	void Update(float time, float delta);
	void Move(int x, int y);
};