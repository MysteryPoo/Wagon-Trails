#pragma once

#include "Entity.h"

class Archer : public Entity
{
public:
	Archer(class app * App);
	Archer(class app * App, int x, int y);
	void Think();
};