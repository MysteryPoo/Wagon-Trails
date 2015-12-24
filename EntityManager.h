#pragma once

#include <unordered_map>
#include <memory>
#include "Entity.h"
#include <string>

using namespace std;

class EntityManager
{
	class app * m_App;
	unsigned m_EntityIndex;
	unordered_map<unsigned, Entity *> * m_Entities;
public:
	EntityManager(class app * App);
	~EntityManager();
	bool EntityAt(int x, int y);
	void RemoveEntity(unsigned index);
	Entity * GetEntity(unsigned index);
	bool GetEntity(Entity * entity);
	unsigned FindNearest(Entity::Type type, unsigned origin, float * distanceResult = nullptr);
	Entity * GetNearest(Entity::Type preferredType, Entity * origin, float range = 500.0f, Entity ** bestTarget = nullptr);
	float GetDistance(unsigned origin, unsigned destination);
	void NewArcher(int x = 0, int y = 0);
	void NewCharacter(Entity::Type type, int x = 0, int y = 0);
	void NewArrow(int x, int y, unsigned targetIndex);
	void NewSpell(int x, int y, unsigned targetIndex);
	void NewEntity(Entity * entity);
	void NewHitEffect(int x, int y);
	void Update(float time, float delta);
};