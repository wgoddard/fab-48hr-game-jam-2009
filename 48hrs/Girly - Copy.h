#pragma once
#include "Player.h"

class Girly :
	public Player
{

public:
	Girly(const char filename[], int x, int y, int w, int h);
	virtual ~Girly(void);
	//virtual void Render();
	//virtual void Update(const float &dt);
	//virtual void AttackA();
	//virtual void AttackB();
	//virtual void AttackC();
	hgeRect GetRect() { hgeRect temp;  m_Sprite->GetBoundingBoxEx(m_X, m_Y, m_Rotation, m_ScaleX/2, m_ScaleY/2, &temp); return temp;}

};
