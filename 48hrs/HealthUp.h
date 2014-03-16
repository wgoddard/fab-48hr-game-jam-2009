#pragma once
#include "powerup.h"

class HealthUp :
	public PowerUp
{
public:
	HealthUp(const char filename[], int x, int y, int w, int h);
	virtual ~HealthUp(void);
	virtual void GetEffect(Player * target) { target->Heal(); m_Consumed = true; }
};
