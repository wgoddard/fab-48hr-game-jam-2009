#include "Weapon.h"

Weapon::Weapon(const char filename[], int x, int y, int w, int h, bool flipx) : Entity(filename, x, y, w, h)
{
	m_Swinging = false;
	m_SwingTime = 0;
}

Weapon::~Weapon(void)
{
}

void Weapon::Render()
{
	m_Sprite->Render(m_X, m_Y);
}

void Weapon::Update(const float &dt)
{
}