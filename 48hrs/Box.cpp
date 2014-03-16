#include "Box.h"

Box::Box(const char filename[], int x, int y, int w, int h, DWORD color) : Entity(filename, x, y, w, h)
{
	m_Sprite->SetHotSpot(0,0);
	m_Sprite->SetColor(color);
}

Box::~Box(void)
{
}

void Box::Update(const float &dt)
{
}

void Box::Render()
{
	m_Sprite->RenderEx(m_X, m_Y, m_Rotation, m_ScaleX, m_ScaleY);
	if (DEBUG)
		RenderBoundingBox();
}