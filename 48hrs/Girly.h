#pragma once
#include "Player.h"

class Girly :
	public Player
{

public:
	Girly(const char filename[], int x, int y, int w, int h);
	virtual ~Girly(void);
	const hgeRect & GetRect() { 
		//if (m_HasMoved)
		{
			m_HasMoved = false;
			m_Sprite->GetBoundingBoxEx(m_X, m_Y, m_Rotation, m_ScaleX/2, m_ScaleY/2, &m_Rect);
		}
		return m_Rect;
	}
	void AttackA()
	{
		if (m_Cooldown <= 0 && (m_Sequence == IDLE || m_Sequence == STEPPING))
			hge->Effect_Play(resource.GetEffect("punch.wav"));
		Player::AttackA();
	}
	void AttackC()
	{
		if (!m_SuperUp)
			return;
		hge->Effect_Play(resource.GetEffect("riot.wav"));
		m_SuperUp = false;
		GENERIC_COUNTDOWN = 1;
		hge->System_SetState(HGE_FRAMEFUNC, riotFrame);
		hge->System_SetState(HGE_RENDERFUNC, riotRender);
		Player::AttackC();
	}
	void Die()
	{
		hge->Effect_Play(resource.GetEffect("girl death.wav"));
	}


};
