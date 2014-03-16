#pragma once
#include "Entity.h"

extern HGE * hge;

class Box :
	public Entity
{
public:
	Box(const char filename[], int x, int y, int w, int h, DWORD color = 0xFFFFFFFF);
	virtual ~Box(void);
	virtual void Update(const float &dt);
	virtual void Render();
};
