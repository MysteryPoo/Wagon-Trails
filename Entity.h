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
	unsigned m_NodeIndex;
	void ClearPath();
	float m_NextThought;
public:
	Entity(class app * App, int x = 0, int y = 0);
	~Entity();
	void Update(float timer, float delta);
	Transform* GetTransform() { return m_Transform; };
	// Grid position to attempt to move to. Will use path finding appropriately.
	void Move(int x, int y);
	virtual void Think() {};
	virtual void Attack() {};
	app * GetAppRef() { return m_AppRef; };
};