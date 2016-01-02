#pragma once

#include "agk.h"
#include "Transform.h"
#include "Attack.h"

class Spell : public Attack
{
public:
	Spell(class app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y);
};