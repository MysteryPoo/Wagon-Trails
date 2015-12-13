// Includes
#include "template.h"

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
	entities = new std::unordered_map<int, std::unique_ptr<Entity>>();
	GUID = 1;
	lastFrame = agk::Timer();

	for (int s = 0; s < 1; ++s)
	{
		NewEntity();
	}

	//camera = new Camera2D();
	camera = new Camera2D(entities->begin()->second->GetTransform());

	//entities->begin()->second->Move(agk::Random(0, 30 * 64), agk::Random(0, 30 * 64));
	
	grid = new CombatGrid(this);
}

void app::Loop (void)
{
	float thisFrame = agk::Timer();
	float diff = thisFrame - lastFrame;
	lastFrame = thisFrame;
	for (auto s = entities->begin(); s != entities->end(); ++s)
	{
		s->second->Update(diff);
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
	entities->insert(std::make_pair<int, std::unique_ptr<Entity>>(GUID++, std::unique_ptr<Entity>(new Entity(this))));
}
