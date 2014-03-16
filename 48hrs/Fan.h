#pragma once
#include "Enemy.h"

class Fan :
	public Enemy
{
private:
	int m_Target;
	hgeRectExt m_TargetBox;
	float m_Angle;
	float m_AngleTarget;
	float m_Timer;
public:
	Fan(const char filename[], int x, int y, int w, int h, float scalex = 1, float scaley = 1, int hp = 1, int damage = 1, bool isboss = false);
	virtual ~Fan(void);
	void AI(float dt);
};
