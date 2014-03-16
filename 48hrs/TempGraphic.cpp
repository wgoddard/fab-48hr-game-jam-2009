#include "TempGraphic.h"

TempGraphic::TempGraphic(const char filename[], int x, int y, int w, int h, float zbuf, bool usehotspot, float lifespan) 
	: StaticGraphic( filename, x, y, w, h, zbuf, usehotspot)
{
	m_Lifespan = lifespan;
	m_Age = 0;
	m_Sprite->SetZ(zbuf);
	m_Sprite->SetTextureRect(hge->Random_Int(0,7) * m_W, 0, m_W, m_H);
	
}

TempGraphic::~TempGraphic(void)
{
}
