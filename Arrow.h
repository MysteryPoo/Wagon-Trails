#pragma once

#include "agk.h"
#include "Transform.h"

class Arrow
{
	class app * m_AppRef;
	int m_Sprite;
	float m_TimeToDie;
	Transform * m_Transform;
public:
	Arrow(class app * App, float time, int x, int y);
	~Arrow();
	void Update(float time, float delta);
};