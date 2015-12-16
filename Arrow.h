#pragma once

#include "agk.h"
#include "Transform.h"
#include "Entity.h"

class Arrow : public Entity
{
	float m_TimeToDie;
	unsigned m_TargetIndex;
	bool m_Hit;
public:
	Arrow(class app * App, unsigned entityIndex, float time, unsigned targetIndex, int x, int y);
	~Arrow();
	void Update(float time, float delta);
	void Move(int x, int y);
};