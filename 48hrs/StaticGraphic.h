#pragma once
#include "Entity.h"

class StaticGraphic :
	public Entity
{
public:
	StaticGraphic(const char filename[], int x, int y, int w, int h, float zbuf = 1.0f, bool usehotspot = false);
	~StaticGraphic(void);
	virtual void Update(const float & dt) {}
	virtual void Render();
	const hgeRect & GetRect() {hgeRect temp; return temp;}
	void MoveLeft(float dt) { m_X-=500*dt; }
};
