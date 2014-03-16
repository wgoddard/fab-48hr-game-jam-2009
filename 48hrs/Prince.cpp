#include "Prince.h"

Prince::Prince(const char filename[], int x, int y, int w, int h) : Entity(filename, x, y, w, h)
{
	m_HP = 300;
	m_MaxHP = 300;
	m_CurrentTime = 0;
	m_CurrentFrame = 0;
}

Prince::~Prince(void)
{
}

void Prince::Update(const float &dt)
{
	m_CurrentTime += dt;
	if (m_CurrentTime > 0.5)
		m_CurrentTime = 0;
	m_CurrentFrame = m_CurrentTime / 0.5 * 4;
}

void Prince::Render()
{
	m_Sprite->SetTextureRect(m_W * m_CurrentFrame, 0, 96, 96);
	m_Sprite->RenderEx(m_X, m_Y, m_Rotation, m_ScaleX, m_ScaleY);
	RenderBar(m_HP, m_MaxHP);
}

int Prince::GetHit(int damage, short type)
{
	m_HP -= damage;
	if (m_HP <= 0)
	{
		hge->System_SetState(HGE_FRAMEFUNC, lastFrame);
		hge->System_SetState(HGE_RENDERFUNC, loseRender);
		return 1;
	}
	RED_FADE_ALPHA = 180;
	return 0;
}