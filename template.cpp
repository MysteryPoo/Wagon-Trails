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
	entities = new std::unordered_map<int, std::unique_ptr<Entity>>();
	GUID = 1;
	lastFrame = agk::Timer();

	for (int s = 0; s < 20; ++s)
	{
		NewEntity();
	}
	camera = new Camera2D(entities->begin()->second->GetTransform());
}

void app::Loop (void)
{
	float thisFrame = agk::Timer();
	float diff = thisFrame - lastFrame;
	lastFrame = thisFrame;
	for (auto s = entities->begin(); s != entities->end(); ++s)
	{
		s->second->Update(thisFrame, diff);
	}
	camera->Update();

	float mouseX = agk::GetPointerX();
	float mouseY = agk::GetPointerY();
	mouseX = agk::ScreenToWorldX(mouseX);
	mouseY = agk::ScreenToWorldY(mouseY);
	int newX = (int)((mouseX + 32) / 64);
	int newY = (int)((mouseY + 32) / 64);
	if(newX >= 0 && newY >= 0 && agk::GetPointerPressed())
		entities->begin()->second->Move(newX, newY);


	agk::Print( agk::ScreenFPS() );
	agk::Sync();
}


void app::End (void)
{
	delete id;
	delete camera;
	entities->clear();
	delete entities;
	delete grid;
}

void app::NewEntity()
{
	int x, y;
	do
	{
		x = agk::Random(0, grid->GetWidth() - 1);
		y = agk::Random(0, grid->GetHeight() - 1);
	} while (!grid->Passable(x, y));
	entities->insert(std::make_pair<int, std::unique_ptr<Entity>>(GUID++, std::unique_ptr<Entity>(new Archer(this, x, y))));
}

bool app::EntityAt(int x, int y)
{
	for (auto s = entities->begin(); s != entities->end(); ++s)
	{
		if (s->second->GetTransform()->getX() == x && s->second->GetTransform()->getY() == y)
		{
			return true;
		}
	}
	return false;
}
