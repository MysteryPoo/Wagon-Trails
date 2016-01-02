#pragma once

#include "agk.h"
#include "Transform.h"
#include "Entity.h"

class Attack : public Entity
{
	float m_TimeToDie;
	unsigned m_SourceIndex;
	unsigned m_TargetIndex;
	bool m_Hit;
public:
	Attack(class app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y);
	~Attack();
	void Update(float time, float delta);
	bool Move(int x, int y);
};