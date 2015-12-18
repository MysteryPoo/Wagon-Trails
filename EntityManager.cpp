#include "EntityManager.h"
#include "agk.h"
#include "template.h"
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