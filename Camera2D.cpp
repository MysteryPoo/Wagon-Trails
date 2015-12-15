#include "Camera2D.h"
#include "agk.h"
#include "template.h"

Camera2D::Camera2D(app * App, unsigned index)
{
	m_App = App;
	this->m_Index = index;
}

Camera2D::~Camera2D()
{
	
}

void Camera2D::Update()
{
	Entity * entity = m_App->GetEntityManager()->GetEntity(m_Index);
	if (entity != nullptr)
	{
		float x = entity->GetTransform()->getSpriteX() - agk::GetVirtualWidth() * 0.5f;
		float y = entity->GetTransform()->getSpriteY() - agk::GetVirtualHeight() * 0.5f;
		agk::SetViewOffset(x, y);
	}
}
