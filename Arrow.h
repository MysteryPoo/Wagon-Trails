#pragma once

#include "agk.h"
#include "Transform.h"
#include "Entity.h"

class Arrow : public Entity
{
	class app * m_App;
	float m_TimeToDie;
public:
	Arrow(class app * App, unsigned entityIndex, float time, int x = 0, int y = 0);
	~Arrow();
	void Update(float time, float delta);
	void Move(int x, int y);
};