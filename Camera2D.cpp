#include "Camera2D.h"
#include "agk.h"

Camera2D::Camera2D()
{
	follow = nullptr;
}

Camera2D::Camera2D(Transform * follow)
{
	Camera2D();
	Assign(follow);
}

Camera2D::~Camera2D()
{
	
}

void Camera2D::Update()
{
	if (follow != nullptr)
	{
		float x = follow->getSpriteX() - agk::GetVirtualWidth() * 0.5f;
		float y = follow->getSpriteY() - agk::GetVirtualHeight() * 0.5f;
		agk::SetViewOffset(x, y);
	}
}
