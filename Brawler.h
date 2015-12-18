#pragma once

#include "Character.h"

class Brawler : public Character
{
public:
	Brawler(class app * App, unsigned entityIndex, int x, int y);
	void Think();
};