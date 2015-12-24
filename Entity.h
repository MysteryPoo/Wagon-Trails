#pragma once

#include "Transform.h"
#include "micropather.h"

using namespace micropather;

class Entity {
protected:
	int m_SpriteIndex;
	unsigned m_EntityIndex;
	class app * m_App;
	Transform * m_Transform;
	bool m_TimeToDie;
public:
	enum Type
	{
		WAGON,
		ARROW,
		OTHER,
		ARCHER,
		MAGE,
		BRAWLER
	};
	Entity(class app * App, unsigned entityIndex, int x = 0, int y = 0);
	virtual ~Entity();
	app * GetAppRef() { return m_App; };
	Transform* GetTransform() { return m_Transform; };
	int GetSprite() { return m_SpriteIndex; };
	Type GetType() { return m_Type; };
	unsigned GetIndex() { return m_EntityIndex; };
	void TimeToDie(bool timeToDie) { m_TimeToDie = timeToDie; };
	bool TimeToDie() { return m_TimeToDie; };
	virtual void Update(float timer, float delta);
	virtual bool Move(int x, int y) =0;
	
protected:
	Type m_Type;
};