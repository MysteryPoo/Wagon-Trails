#pragma once

#include "Transform.h"
#include "micropather.h"

using namespace micropather;

class Entity {
protected:
	int m_SpriteIndex;
	class app * m_AppRef;
	Transform * m_Transform;
public:
	Entity(class app * App, int x = 0, int y = 0);
	~Entity();
	app * GetAppRef() { return m_AppRef; };
	Transform* GetTransform() { return m_Transform; };
	virtual void Update(float timer, float delta);
	virtual void Move(int x, int y) =0;
};