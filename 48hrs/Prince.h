#pragma once
#include "entity.h"

class Prince :
	public Entity
{
private:
	int m_HP;
	int m_MaxHP;
	float m_CurrentTime;
	int m_CurrentFrame;
public:
	Prince(const char filename[], int x, int y, int w, int h);
	virtual ~Prince(void);
	virtual void Update(const float &dt);
	virtual void Render();
	int GetHit(int damage, short type);
};
