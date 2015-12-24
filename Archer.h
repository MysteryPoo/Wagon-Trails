#pragma once

#include "Hireling.h"

class Archer : public Hireling
{
public:
	Archer(class app * App, unsigned entityIndex, int x, int y);
	void Think();
	void Attack();
};