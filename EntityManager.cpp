#include "EntityManager.h"
#include "agk.h"
#include "template.h"
#include "Archer.h"
#include "Arrow.h"

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
		if (s->second->GetTransform()->getX() == x && s->second->GetTransform()->getY() == y)
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

void EntityManager::NewArrow(int x, int y, unsigned targetIndex)
{
	while (GetEntity(m_EntityIndex) != nullptr)
		++m_EntityIndex;
	m_Entities->insert(std::make_pair<unsigned, Entity*>(m_EntityIndex++, new Arrow(m_App, m_EntityIndex, agk::Timer(), targetIndex, x, y)));
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
