#pragma once
#include "weapon.h"

class HandBag :
	public Weapon
{
public:
	HandBag(const char filename[], int x, int y, int w, int h, bool flipx);
	virtual ~HandBag(void);
	void Render();
	void Update(const float & dt);
};
