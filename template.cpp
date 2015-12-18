// Includes
#include "template.h"
#include "Archer.h"

// Namespace
using namespace AGK;

app App;

void app::Begin(void)
{
	agk::SetVirtualResolution(1024, 768);
	//agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetClearColor(100, 200, 60);
	agk::SetSyncRate(60, 0);
	agk::SetScissor(0, 0, 0, 0);

	id = new ImageDatabase();
	grid = new CombatGrid(this);
	m_EntityManager = new EntityManager(this);
	lastFrame = agk::Timer();

	for (int s = 0; s < 12; ++s)
	{
		m_EntityManager->NewArcher();
	}
	camera = new Camera2D(this, 0);
}

void app::Loop (void)
{
	float thisFrame = agk::Timer();
	float diff = thisFrame - lastFrame;
	lastFrame = thisFrame;
	m_EntityManager->Update(thisFrame, diff);
	camera->Update();

	float mouseX = agk::GetPointerX();
	float mouseY = agk::GetPointerY();
	mouseX = agk::ScreenToWorldX(mouseX);
	mouseY = agk::ScreenToWorldY(mouseY);
	int newX = (int)((mouseX + 32) / 64);
	int newY = (int)((mouseY + 32) / 64);
	if (newX >= 0 && newY >= 0 && agk::GetPointerPressed())
	{
		if (m_EntityManager->GetEntity(0) != nullptr)
		{
			m_EntityManager->GetEntity(0)->Move(newX, newY);
			m_EntityManager->NewArrow(m_EntityManager->GetEntity(0)->GetTransform()->getX(),
				m_EntityManager->GetEntity(0)->GetTransform()->getY(),
				m_EntityManager->FindNearest(Entity::ARCHER, 0));
		}
	}

	agk::Print( agk::ScreenFPS() );
	agk::Sync();
}


void app::End (void)
{
	delete id;
	delete camera;
	delete grid;
}