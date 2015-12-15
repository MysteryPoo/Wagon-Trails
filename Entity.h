#pragma once

#include "Transform.h"
#include "micropather.h"

using namespace micropather;

class Entity {
protected:
	int m_SpriteIndex;
	unsigned m_EntityIndex;
	class app * m_AppRef;
	Transform * m_Transform;
	bool m_TimeToDie;
public:
	Entity(class app * App, unsigned entityIndex, int x = 0, int y = 0);
	~Entity();
	app * GetAppRef() { return m_AppRef; };
	Transform* GetTransform() { return m_Transform; };
	void TimeToDie(bool timeToDie) { m_TimeToDie = timeToDie; };
	bool TimeToDie() { return m_TimeToDie; };
	virtual void Update(float timer, float delta);
	virtual void Move(int x, int y) =0;
};