#pragma once

#include "agk.h"
#include "Transform.h"
#include "Attack.h"

class Arrow : public Attack
{
public:
	Arrow(class app * App, unsigned entityIndex, float timeToDie, unsigned sourceIndex, unsigned targetIndex, int x, int y);
};