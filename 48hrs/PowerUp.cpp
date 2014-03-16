#include "PowerUp.h"

PowerUp::PowerUp(const char filename[], int x, int y, int w, int h) : Entity(filename, x, y, w, h)
{
	m_Consumed = false;
}

PowerUp::~PowerUp(void)
{
}

void PowerUp::Render()
{
	m_Sprite->Render(m_X, m_Y);
}