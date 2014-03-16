#pragma once
#include "entity.h"
#include "hgeparticle.h"

class Player :
	public Entity
{
protected:
	enum m_Sequences{IDLE, ATTACKA, ATTACKB, ATTACKC, DEATH, STEPPING, FANFARE, HIT};
	enum m_Statuses{NORMAL};
	int m_HP;
	int m_MaxHP;
	int m_Sequence;
	int m_Status;
	float m_MaxVelocity;

	int m_DamageA;
	int m_DamageB;
	int m_DamageC;

	float m_Invulnerable;
	float m_SpeedUp;

	float m_Cooldown;

	float m_CooldownA;
	float m_CooldownB;
	float m_CooldownC;

	int m_CurrentFrame;
	float m_CurrentTime;

	float m_Time[8];
	int m_Frames[8];

	int m_Kills;
	int m_Score;

	double m_Angle;

	bool m_SuperUp;
	hgeParticleSystem*	par;

	hgeSprite * m_Particles;
public:
	Player(const char filename[], int x, int y, int w, int h);
	virtual ~Player(void);
	virtual void Render();
	virtual void Update(const float &dt);
	virtual int GetHit(int damage, short type);
	virtual void Move(int magnitude_x, int magnitude_y, float dt);
	virtual void AttackA();
	virtual void AttackB();
	virtual void AttackC();
	virtual void ResetPosition (float x, float y);
	//virtual bool IsAlive();
	int GetScore() { return m_Score;} 
	void AddScore(int amount) {m_Score += amount;}
	void Heal() { m_HP = m_MaxHP; }
	void SpeedUp(float time) { m_SpeedUp += time; }
	void SuperUp() { m_SuperUp = true; }
	virtual void Die() {}
	virtual bool IsAlive() { if (m_HP <= 0) return false; else return true; }
	//hgeRect GetRect() { m_W/=2; hgeRect temp = Entity::GetRect(); m_W*=2; return temp;}
};
