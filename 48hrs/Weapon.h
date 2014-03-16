#pragma once
#include "Entity.h"

class Weapon :
	public Entity
{
protected:
	float m_SwingTime;
	bool m_Swinging;
public:
	Weapon(const char filename[], int x, int y, int w, int h, bool flipx);
	virtual ~Weapon(void);
	virtual void Render();
	virtual void Update(const float &dt);
	virtual void StartSwing(float time);
	virtual void StopSwing();
};
