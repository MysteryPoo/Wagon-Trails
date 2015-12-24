#pragma once

#include "Hireling.h"

class Brawler : public Hireling
{
public:
	Brawler(class app * App, unsigned entityIndex, int x, int y);
	void Think();
	void Attack();
};