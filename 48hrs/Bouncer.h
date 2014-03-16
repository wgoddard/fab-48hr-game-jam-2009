#pragma once
#include "Girly.h"

class Bouncer :
	public Girly
{
public:
	Bouncer(const char filename[], int x, int y, int w, int h);
	virtual ~Bouncer(void);
	void AttackA()
	{
		if (m_Cooldown <= 0 && (m_Sequence == IDLE || m_Sequence == STEPPING))
		{
			hge->Effect_Play(resource.GetEffect("shot.wav"));
			par->FireAt(m_X, m_Y);
			par->Transpose(cos(m_Angle) * 50, sin(m_Angle) * 50);
			//par->info.fDirection = m_Angle;
		}
		Player::AttackA();
	}
	void AttackC()
	{
		if (!m_SuperUp)
			return;
		hge->Effect_Play(resource.GetEffect("obscenity.mp3"));
		m_SuperUp = false;
		GENERIC_COUNTDOWN = 1;
		hge->System_SetState(HGE_FRAMEFUNC, obscenityFrame);
		hge->System_SetState(HGE_RENDERFUNC, obscenityRender);
		Player::AttackC();
	}
	void Die()
	{
		hge->Effect_Play(resource.GetEffect("blood splat.wav"));
	}
};
