#pragma once

#include "Hireling.h"

class Mage : public Hireling
{
public:
	Mage(class app * App, unsigned entityIndex, int x, int y);
	void Think();
	void Attack();
	void Update(float time, float delta);
};