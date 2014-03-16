#include "Bouncer.h"

Bouncer::Bouncer(const char filename[], int x, int y, int w, int h) : Girly(filename, x, y, w, h)
{
	m_HP = 50;
	m_MaxHP = 50;
	m_Sequence = 0;
	m_Status = NORMAL;
	m_MaxVelocity = 200;

	m_DamageA = 2;
	m_DamageB = 3;
	m_DamageC = 50;

	m_Cooldown = 0;

	m_CooldownA = 0;
	m_CooldownB = 0;
	m_CooldownC = 1;

	m_CurrentFrame = 0;
	m_CurrentTime = 0;

	float Time[8] = {1, .35, .5, 1, 1, 0.5, 1, 0.5};
	int Frames[8] = {1, 5, 5, 1, 9, 4, 1, 1};
	for (int i = 0; i < 8; ++i)
	{
		m_Frames[i] = Frames[i];
		m_Time[i] = Time[i];
	}

	par = new hgeParticleSystem("shotgun.psi", m_Particles);
}

Bouncer::~Bouncer(void)
{
}
