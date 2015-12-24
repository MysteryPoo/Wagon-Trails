#pragma once

#include "Entity.h"

class Hireling : public Entity
{
	MPVector<void*> m_Path;
	unsigned m_NodeIndex;
protected:
	float m_NextThought;
	float m_NextAttack;
	int m_HealthMax;
	int m_Health;
	//Entity * m_Best, * m_Nearest; // Change to indices and grab the reference each time to ensure they exist still. GetEntity()
	unsigned m_Best, m_Nearest;
public:
	Hireling(class app * App, unsigned entityIndex, int x = 0, int y = 0);
	virtual void Think() =0;
	virtual void Attack() {};
	virtual void Damage(int damage);
	float GetHealth() { return (float)m_Health / (float)m_HealthMax; };
	virtual void Update(float time, float delta);
	bool Move(int x, int y);
};