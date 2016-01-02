#pragma once

#include "Hireling.h"

class Archer : public Hireling
{
public:
	Archer(class app * App, unsigned entityIndex, unsigned wagon, int x, int y);
	void Think();
	void Attack();
};