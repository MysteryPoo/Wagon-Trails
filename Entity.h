#pragma once

#include "Transform.h"

class Entity {
	enum {
		IDLE
	} State;

	int m_SpriteIndex;
	class app * m_AppRef;
	int m_Speed;
	Transform * m_Position;
public:
	Entity(class app * App);
	~Entity();
	void Update(float delta);
	Transform* GetTransform() { return m_Position; };
};