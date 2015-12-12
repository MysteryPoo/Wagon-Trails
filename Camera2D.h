#pragma once

#include "Transform.h"

class Camera2D
{
	Transform *follow;
public:
	Camera2D(Transform * follow = nullptr);
	~Camera2D();
	void Assign(Transform *follow) { this->follow = follow; };
	void Unassign() { follow = nullptr; }
	Transform* getAssigned() { return follow; }
	void Update();
};