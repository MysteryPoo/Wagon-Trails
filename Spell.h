#pragma once

#include "agk.h"
#include "Transform.h"
#include "Entity.h"

class Spell : public Entity
{
	float m_TimeToDie;
	unsigned m_TargetIndex;
	bool m_Hit;
public:
	Spell(class app * App, unsigned entityIndex, float time, unsigned targetIndex, int x, int y);
	~Spell();
	void Update(float time, float delta);
	bool Move(int x, int y);
};