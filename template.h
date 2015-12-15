#ifndef _H_SMACKIT_
#define _H_SMACKIT_

// Link to GDK libraries
#include "agk.h"
#include "ImageDatabase.h"
#include "Camera2D.h"
#include "CombatGrid.h"
#include "EntityManager.h"

#define DEVICE_WIDTH 1024
#define DEVICE_HEIGHT 768
#define DEVICE_POS_X 32
#define DEVICE_POS_Y 32
#define FULLSCREEN false

// Global values for the app
class app
{
	ImageDatabase *id;
	float lastFrame;
	Camera2D *camera;
	CombatGrid * grid;
	EntityManager * m_EntityManager;
	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions - mike to experiment with a derived class for this..
		void Begin( void );
		void Loop( void );
		void End( void );

		ImageDatabase* getImageDatabase() { return id; }
		Camera2D* getCamera() { return camera; }
		CombatGrid * getCombatGrid() { return grid; };
		EntityManager * GetEntityManager() { return m_EntityManager; };
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif