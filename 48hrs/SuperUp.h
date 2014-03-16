#pragma once
#include "powerup.h"

class SuperUp :
	public PowerUp
{
public:
	SuperUp(const char filename[], int x, int y, int w, int h);
	virtual ~SuperUp(void);
	virtual void GetEffect(Player * target) { target->SuperUp(); m_Consumed = true; }
};
