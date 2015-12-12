#pragma once

#include "Transform.h"
#include "micropather.h"

using namespace micropather;

class Entity {
	enum {
		IDLE
	} State;

	int m_SpriteIndex;
	class app * m_AppRef;
	Transform * m_Transform;
	MPVector<void*> m_Path;
	int m_NodeIndex;
	void ClearPath();
public:
	Entity(class app * App);
	~Entity();
	void Update(float delta);
	Transform* GetTransform() { return m_Transform; };
	void Move(int x, int y);
};