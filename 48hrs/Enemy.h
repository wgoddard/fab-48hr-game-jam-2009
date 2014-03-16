#pragma once
#include "entity.h"


class Enemy :
	public Entity
{
protected:
	enum m_Sequences{IDLE, ATTACK, BLANKA, BLANKB, DEATH, STEPPING, FANFARE, HIT};
	enum m_Statuses{NORMAL};
	int m_HP;
	int m_MaxHP;
	int m_Sequence;
	int m_Status;
	float m_MaxVelocity;
	int m_Damage;
	float m_Cooldown;
	float m_CooldownAttack;
	int m_CurrentFrame;
	float m_CurrentTime;
	int m_Kills;

	//float m_MathTimer;

	int m_Value;

	float m_Time[8];
	int m_Frames[8];
	float m_Angle;

	virtual void AI(float dt) = 0;
public:
	Enemy(const char filename[], int x, int y, int w, int h, float scalex, float scaley, int hp, int damage);
	virtual ~Enemy(void);
	virtual void Render() ;
	virtual void Update(const float &dt);
	int GetHit(int damage, short type);
	const hgeRect & GetRect() { 
		//if (m_HasMoved)
		{
			m_HasMoved = false;
			m_Sprite->GetBoundingBoxEx(m_X, m_Y, m_Rotation, m_ScaleX/2, m_ScaleY/2, &m_Rect);
		}
		return m_Rect;
	}
	bool IsAlive();
	virtual void AttackA();
};
