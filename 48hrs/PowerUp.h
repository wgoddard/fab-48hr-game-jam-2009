#pragma once
#include "entity.h"
#include "player.h"

class PowerUp :
	public Entity
{
protected:
	bool m_Consumed;
public:
	PowerUp(const char filename[], int x, int y, int w, int h);
	virtual ~PowerUp(void);
	virtual void Render();
	virtual void Update(const float &dt) {}
	virtual void GetEffect(Player * target) {}
	virtual bool IsAlive() { return !m_Consumed;}
};
