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
	entities = new std::unordered_map<int, std::unique_ptr<Entity>>;
	GUID = 1;
	lastFrame = agk::Timer();

	for (int s = 0; s < 1; ++s)
	{
		NewEntity();
	}

	//camera = new Camera2D();
	camera = new Camera2D(entities->begin()->second->GetTransform());
	
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
	agk::Print( agk::ScreenFPS() );
	agk::Print(entities->begin()->second->GetTransform()->getX());
	agk::Print(entities->begin()->second->GetTransform()->getY());
	agk::Print(entities->begin()->second->GetTransform()->getSpeed());
	agk::Sync();
}


void app::End (void)
{
	delete id;
	delete camera;
	entities->clear();
}

void app::NewEntity()
{
	entities->insert(std::make_pair<int, std::unique_ptr<Entity>>(GUID++, std::unique_ptr<Entity>(new Entity(this))));
}
