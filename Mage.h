#pragma once

#include "Character.h"

class Mage : public Character
{
public:
	Mage(class app * App, unsigned entityIndex, int x, int y);
	void Think();
};