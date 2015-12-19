#pragma once

#include "Character.h"

class Wagon : public Character
{
public:
	Wagon(class app * App, unsigned entityIndex, int x, int y);
	void Think();
};