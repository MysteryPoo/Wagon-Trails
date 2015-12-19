#pragma once

#include "Entity.h"

class Character : public Entity
{
	MPVector<void*> m_Path;
	unsigned m_NodeIndex;
protected:
	float m_NextThought;
	float m_NextAttack;
	int m_HealthMax;
	int m_Health;
public:
	Character(class app * App, unsigned entityIndex, int x = 0, int y = 0);
	virtual void Think() =0;
	virtual void Attack() {};
	virtual void Damage(int damage);
	float GetHealth() { return (float)m_Health / (float)m_HealthMax; };
	virtual void Update(float time, float delta);
	bool Move(int x, int y);
};