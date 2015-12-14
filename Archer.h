#pragma once

#include "Character.h"

class Archer : public Character
{
public:
	Archer(class app * App, int x, int y);
	void Think();
};