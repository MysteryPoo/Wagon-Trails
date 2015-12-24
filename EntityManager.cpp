#include "EntityManager.h"
#include "agk.h"
#include "template.h"
#include "Wagon.h"
#include "Archer.h"
#include "Mage.h"
#include "Brawler.h"
#include "Arrow.h"
#include "Spell.h"
#include "Effect.h"
#include <cstdarg>

EntityManager::EntityManager(app * App)
{
	m_App = App;
	m_EntityIndex = 0;
	m_Entities = new unordered_map<unsigned, Entity*>();
}

EntityManager::~EntityManager()
{
	for (auto s = m_Entities->begin(); s != m_Entities->end(); ++s)
	{
		delete s->second;
	}
	delete m_Entities;
}

bool EntityManager::EntityAt(int x, int y)
{
	for (auto s = m_Entities->begin(); s != m_Entities->end(); ++s)
	{
		if (s->second->GetType() != Entity::ARROW &&
			s->second->GetTransform()->getX() == x &&
			s->second->GetTransform()->getY() == y)
		{
			return true;
		}
	}
	return false;
}

void EntityManager::RemoveEntity(unsigned index)
{
	GetEntity(index)->TimeToDie(true);
}

Entity * EntityManager::GetEntity(unsigned index)
{
	unordered_map<unsigned, Entity*>::const_iterator it = m_Entities->find(index);
	if (it != m_Entities->end())
	{
		Entity * entity = it->second;
		return entity;
	}
	return nullptr;
}

bool EntityManager::GetEntity(Entity * entity)
{

	return false;
}

unsigned EntityManager::FindNearest(Entity::Type type, unsigned origin, float * distanceResult)
{
	float distance = 500.0f;
	auto nearest = m_Entities->begin();
	int x = GetEntity(origin)->GetTransform()->getX();
	int y = GetEntity(origin)->GetTransform()->getY();
	for (auto e = nearest; e != m_Entities->end(); ++e)
	{
		if (e->first != origin && e->second->GetType() == type)
		{
			int dx = e->second->GetTransform()->getX() - x;
			int dy = e->second->GetTransform()->getY() - y;
			float dist = agk::Sqrt((float)dx*(float)dx + (float)dy*(float)dy);
			if (dist < distance)
			{
				distance = dist;
				nearest = e;
			}
		}
	}
	if (distanceResult != nullptr)
		*distanceResult = distance;
	return nearest->first;
}

Entity * EntityManager::GetNearest(Entity::Type preferredType, Entity * origin, float range, Entity ** bestTarget)
{
	// Cache the x & y of the origin Entity
	int ox = origin->GetTransform()->getX();
	int oy = origin->GetTransform()->getY();
	// range is the distance to beat
	float bestDistance = range, nearestDistance = range;
	// We'll return nullptr if we can't find anything
	Entity * nearest = nullptr;
	// Iterate through all our entities
	for (auto e = m_Entities->begin(); e != m_Entities->end(); ++e)
	{
		// If we're checking our origin object, we need to skip it
		if (e->second != origin)
		{
			// Calculate the x distance
			int dx = e->second->GetTransform()->getX() - ox;
			int dy;
			// Slight optimization here to avoid unnecessary sqrt calls
			// Both x and y deltas must beat the range independently if the true distance also beats the range
			if (dx <= range)
				// Calculate the y distance
				dy = e->second->GetTransform()->getY() - oy;
			else
				// If delta x is bigger than the range, we'll skip to the next entity
				continue;
			// Cache the type of entity this is
			Entity::Type type = e->second->GetType();
			// If our x and y deltas are good and we're a Hireling (valid entity), let's continue to calculate true distance
			if (dy <= range && (
				type == Entity::ARCHER ||
				type == Entity::BRAWLER ||
				type == Entity::MAGE))
			{
				// Basic distance formula
				float distance = agk::Sqrt(dx*dx + dy*dy);
				// If this distance beats our nearest distance
				if (distance < nearestDistance)
				{
					// This becomes the closest entity
					nearest = e->second;
					nearestDistance = distance;
				}
				// If we're checking for best target and this entity is what we're looking for...
				if (bestTarget != nullptr && type == preferredType && distance < bestDistance)
				{
					// ...this becomes the best entity
					bestTarget = &e->second;
					bestDistance = distance;
				}
			}
		}
	}
	return nearest;
}

float EntityManager::GetDistance(unsigned origin, unsigned destination)
{
	Entity * ent1 = GetEntity(origin);
	Entity * ent2 = GetEntity(destination);
	if (ent1 == nullptr || ent2 == nullptr)
		return 100.0f;
	float dx = (float)(ent2->GetTransform()->getX() - ent1->GetTransform()->getX());
	float dy = (float)(ent2->GetTransform()->getY() - ent1->GetTransform()->getY());
	return agk::Sqrt(dx*dx + dy*dy);
}

void EntityManager::NewArcher(int x, int y)
{
	if (x == 0 && y == 0)
	{
		do
		{
			x = agk::Random(0, m_App->getCombatGrid()->GetWidth() - 1);
			y = agk::Random(0, m_App->getCombatGrid()->GetHeight() - 1);
		} while (!m_App->getCombatGrid()->Passable(x, y));
	}
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Archer(m_App, m_EntityIndex, x, y)));
}

void EntityManager::NewCharacter(Entity::Type type, int x, int y)
{
	if (x == 0 && y == 0)
	{
		do
		{
			x = agk::Random(0, m_App->getCombatGrid()->GetWidth() - 1);
			y = agk::Random(0, m_App->getCombatGrid()->GetHeight() - 1);
		} while (!m_App->getCombatGrid()->Passable(x, y));
	}
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	switch (type)
	{
	case Entity::WAGON:
		m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Wagon(m_App, m_EntityIndex, x, y)));
		break;
	case Entity::ARCHER:
		m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Archer(m_App, m_EntityIndex, x, y)));
		break;
	case Entity::MAGE:
		m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Mage(m_App, m_EntityIndex, x, y)));
		break;
	case Entity::BRAWLER:
		m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Brawler(m_App, m_EntityIndex, x, y)));
		break;
	}
}

void EntityManager::NewArrow(int x, int y, unsigned targetIndex)
{
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Arrow(m_App, m_EntityIndex, agk::Timer(), targetIndex, x, y)));
}

void EntityManager::NewSpell(int x, int y, unsigned targetIndex)
{
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Spell(m_App, m_EntityIndex, agk::Timer(), targetIndex, x, y)));
}

void EntityManager::NewEntity(Entity * entity)
{
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair(m_EntityIndex++, entity));
}

void EntityManager::NewHitEffect(int x, int y)
{
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair(m_EntityIndex++, new Effect(m_App, m_EntityIndex, agk::Timer(), x, y)));
}

void EntityManager::Update(float time, float delta)
{
	auto e = m_Entities->begin();
	while (e != m_Entities->end())
	{
		e->second->Update(time, delta);
		if (e->second->TimeToDie())
		{
			delete e->second;
			e = m_Entities->erase(e);
		}
		else
		{
			++e;
		}
	}
}
