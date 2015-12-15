#pragma once

#include "Character.h"

class Archer : public Character
{
public:
	Archer(class app * App, unsigned entityIndex, int x, int y);
	void Think();
};