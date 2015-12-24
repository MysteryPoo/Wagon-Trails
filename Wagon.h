#pragma once

#include "Hireling.h"

class Wagon : public Hireling
{
public:
	Wagon(class app * App, unsigned entityIndex, int x, int y);
	void Think();
};