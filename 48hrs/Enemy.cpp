#include "Enemy.h"
#include "Bullet.h"
#include "TempGraphic.h"

extern std::vector <TempGraphic *> tempGraphics;
extern std::vector <Bullet *> bullets;

Enemy::Enemy(const char filename[], int x, int y, int w, int h, float scalex, float scaley, int hp, int damage) : Entity(filename, x, y, w, h)
{
	m_Cooldown = 0;
	m_CurrentFrame = 0;
	m_CurrentTime = 0;
	m_Angle = 0;
	m_ScaleX = scalex;
	m_ScaleY = scaley;
	m_Kills = 0;
	//m_MathTimer = 0;

}

Enemy::~Enemy(void)
{
}

int Enemy::GetHit(int damage, short type)      // int GetHit(int damage, short type)
{
	if (m_Sequence == DEATH)
		return 0;
	//std::cout << "HIT\n";
	m_HP -= damage;
	if (m_HP <= 0)
	{
		m_CurrentTime = 0;
		m_CurrentFrame = 0;
		m_Sequence = DEATH;
		//std::cout << "DEAD\n";
		tempGraphics.push_back(new TempGraphic("splat.png", m_X, m_Y, 96, 96, 0.9, true, 5));
		return m_Value;
	}
	return 0;
}

void Enemy::Render()
{
	//if (m_HP <= 0 && m_CurrentTime >= m_Time[DEATH])
	//	return;
	//	enum m_Sequences(IDLE, ATTACK, DEATH, STEPPING, FANFARE, HIT);
	m_Sprite->SetZ(0.8 - (m_Y/S_HEIGHT * 0.5f));
	m_Sprite->SetTextureRect(m_W * m_CurrentFrame, m_H * m_Sequence, m_W, m_H);
	m_Sprite->SetFlip(m_FlipX, m_FlipY, true);
	m_Sprite->RenderEx(m_X, m_Y, m_Rotation, m_ScaleX, m_ScaleY);
	if (DEBUG)
		RenderBoundingBox();
}

void Enemy::Update(const float &dt)
{
	AI(dt);
	m_CurrentTime += dt;
	//m_MathTimer -= dt;

	if (m_Cooldown > 0)
		m_Cooldown -= dt;


	//enum m_Sequences{IDLE, ATTACKA, ATTACKB, ATTACKC, DEATH, STEPPING, FANFARE, HIT};

	if (m_Sequence == IDLE)
		m_Sequence = STEPPING;

	if (m_CurrentTime > m_Time[m_Sequence] && m_Sequence != DEATH)
	{
		m_CurrentTime = 0;
		if (m_Sequence != IDLE && m_Sequence != ATTACK)
			m_Sequence = IDLE;
	}
	m_CurrentFrame = m_CurrentTime / m_Time[m_Sequence] * m_Frames[m_Sequence];

	for (unsigned int i = 0; i < bullets.size(); ++i)
	{
		//if (bullets[i]->GetRect().Intersect(&GetRect()))
		if (GetRect().Intersect(&bullets[i]->GetRect()))
		{
			bullets[i]->IsHit(this);
			//std::cout << "Yo mofo\n";
		}
	}
}

bool Enemy::IsAlive()
{
	//lstd::cout << "CTime " << m_CurrentTime << " timetodie " << m_Time[DEATH] << " hp " << m_HP << '\n';
	if (m_Sequence == DEATH && m_CurrentTime >= m_Time[DEATH])
		return false;
	else
		return true;
}

void Enemy::AttackA()
{
	hgeRectExt temp = CreateTargetBox(m_W/2 * cos(m_Angle), m_H/2 * sin(m_Angle), m_W/2, m_H/2, false);
}