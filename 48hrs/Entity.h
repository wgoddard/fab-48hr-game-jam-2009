#pragma once

#include "global.h"
#include "hgeRectExt.h"

class Entity
{
private:
	HTEXTURE m_Texture;
protected:
	hgeSprite * m_Sprite;   //Constructor sets hotspot by default to center point
	float m_X, m_Y; //Changed from double to flaot on 12 of sept.
	float m_W, m_H;
	float m_Rotation;
	float m_ScaleX;
	float m_ScaleY;
	bool m_FlipX;
	bool m_FlipY;
	hgeRectExt CreateTargetBox(float xoffset, float yoffset, const float & sizex, const float & sizey, const bool usedirection = false);
	bool MoveEx(float dt, float MagnitudeX, float MagnitudeY = 0.0f, bool forcemove = false);
	bool m_IsBoss;
	hgeRect m_Rect;
	bool m_HasMoved;
public:
	Entity(const char filename[], int x, int y, int w, int h);
	//Entity(Entity & e);
	//virtual Entity & operator=(const Entity & e);
	virtual ~Entity(void);
	void SetPosition(float x, float y) { m_X = x, m_Y = y; }
	virtual void Update (const float &dt) = 0;
	virtual void Render() = 0;
	virtual void RenderBar(	const float & current, const float & maximum, float xoffset = 0, float yoffset = -20, const float sizex = 50,
							const DWORD barcolor = 0xFFFFFFFF, const DWORD linecolor = 0xFF23A0E0);
	virtual void RenderBoundingBox();
	const virtual hgeRect & GetRect() {
		if (m_HasMoved)
			{
				m_HasMoved = false;
				m_Sprite->GetBoundingBoxEx(m_X, m_Y, m_Rotation, m_ScaleX, m_ScaleY, &m_Rect);
		}
		return m_Rect;
	}
	hgeSprite & GetSprite() { return *m_Sprite; }
	virtual bool IsAlive() {return true;}
	float GetX() { return m_X; }
	float GetY() { return m_Y; }
	float GetW() { return m_W; }
	float GetH() { return m_H; }
	virtual int GetHit(int damage, short type) { return 0;}
	virtual void AddScore(int amount){}
	virtual bool IsBoss() { return m_IsBoss; }
	bool Collide();
};
