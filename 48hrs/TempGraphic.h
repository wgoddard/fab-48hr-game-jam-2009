#pragma once
#include "staticgraphic.h"

class TempGraphic :
	public StaticGraphic
{
private:
	float m_Lifespan;
	float m_Age;
public:
	TempGraphic(const char filename[], int x, int y, int w, int h, float zbuf, bool usehotspot, float lifespawn = 2);
	virtual ~TempGraphic(void);
	void Update(const float & dt) {
		m_Age += dt;
		int alpha = 255 - m_Age/m_Lifespan * 255;
		m_Sprite->SetColor( alpha << 24 | 0xFFFFFF);
	}
	bool IsAlive() { if (m_Age < m_Lifespan) return true; else return false;}
};
