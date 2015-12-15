#pragma once

class Camera2D
{
	class app * m_App;
	unsigned m_Index;
public:
	Camera2D(class app * App, unsigned index);
	~Camera2D();
	void Assign(unsigned index) { this->m_Index = index; };
	unsigned GetAssigned() { return m_Index; }
	void Update();
};