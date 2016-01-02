#pragma once

#include "Hireling.h"

class Wagon : public Hireling
{
public:
	enum Mode
	{
		PACKED,
		ESCORT,
		DEPLOYED
	};
	Wagon(class app * App, unsigned entityIndex, unsigned wagon, int x, int y);
	void Think();
};