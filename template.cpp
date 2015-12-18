// Includes
#include "template.h"
#include "Archer.h"
#include "Mage.h"

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
		int r = agk::Random(0, 100);
		if (r > 90)
			m_EntityManager->NewCharacter(Entity::ARCHER);
		else if(r >50)
			m_EntityManager->NewCharacter(Entity::MAGE);
		else
			m_EntityManager->NewCharacter(Entity::BRAWLER);
		//m_EntityManager->NewArcher();
	}
	cameraTrack = 0;
	camera = new Camera2D(this, cameraTrack);
}

void app::Loop (void)
{
	float thisFrame = agk::Timer();
	float diff = thisFrame - lastFrame;
	lastFrame = thisFrame;
	m_EntityManager->Update(thisFrame, diff);
	if (m_EntityManager->GetEntity(cameraTrack) == nullptr)
	{
		camera->Assign(++cameraTrack);
	}
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
				m_EntityManager->FindNearest(Entity::MAGE, 0));
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