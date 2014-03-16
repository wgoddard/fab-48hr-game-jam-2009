#pragma once
#include "entity.h"
#include "hgeparticle.h"

class Bullet :
	public Entity
{
private:
	int m_Velocity;
	float m_Angle;
	int m_Damage;
	bool m_Alive;
	Entity * m_Parent;
	hgeParticleSystem*	par;
public:
	Bullet(const char filename[], int x, int y, int w, int h, int velocity, double angle, int damage, Entity * parent);
	virtual ~Bullet(void);
	void Update (const float &dt);
	void Render();
	bool IsAlive();
	void IsHit (Entity * target) {
		if (m_Alive)
		{
			//std::cout << "I do " << m_Damage << " damage.\n";
			int score = target->GetHit(m_Damage, 0);
			//std::cout << "I got " << score << " score.\n";
			m_Parent->AddScore(score);
			if (target->IsBoss())
				m_Alive = false;
		}
	}
};
