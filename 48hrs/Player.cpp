#include "Player.h"
#include <cmath>

#include "Enemy.h"
#include "Bullet.h"
#include "Powerup.h"

extern std::vector <hgeRectExt>		tempBoundingBoxes;
extern std::vector <Enemy *> enemies;
extern std::vector <Bullet *> bullets;
extern std::vector <PowerUp *> powerups;


Player::Player(const char filename[], int x, int y, int w, int h) : Entity(filename, x, y, w, h)
{
	m_Kills = 0;
	m_Score = 0;
	m_Angle = 0;
	m_Invulnerable = 0;
	m_SuperUp = false;
	par = NULL;
	m_Particles = new hgeSprite(resource.GetTexture("particles.png"), 96, 0, 32, 32);
	m_Particles->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_ZWRITE);
}

Player::~Player(void)
{
	delete par;
	delete m_Particles;
}

void Player::Render()
{
	//	enum m_Sequences(IDLE, ATTACKA, ATTACKB, ATTACKC, DEATH, STEPPING, FANFARE, HIT);
	m_Sprite->SetTextureRect(m_W * m_CurrentFrame, m_H * m_Sequence, m_W, m_H);
	m_Sprite->SetFlip(m_FlipX, m_FlipY, true);
	m_Sprite->RenderEx(m_X, m_Y, m_Rotation, m_ScaleX, m_ScaleY);

	RenderBar(m_HP, m_MaxHP);
	
	if (par != NULL)
		par->Render();

	if (DEBUG)
		RenderBoundingBox();
}

void Player::Update(const float &dt)
{
	if (m_SpeedUp > 0)
	{
		//do it twice as fast
		m_SpeedUp -= dt;
	}

	if (par != NULL)
	{
		par->Update(dt);
	}

	m_CurrentTime += dt;
	if (m_Cooldown > 0)
		m_Cooldown -= dt;




	//revive
	if (m_Sequence == DEATH && m_Cooldown <= 0)
	{
		m_Sequence = IDLE;
		m_Invulnerable = 2;

		do
		{
			m_X = hge->Random_Int(300, 500);
			m_Y = hge->Random_Int(400, S_HEIGHT-150);
			static int i = 0;
			i++;
			if (i > 20)
				break;
		}
		while (Collide());

		//ResetPosition(hge->Random_Int(300, 500), hge->Random_Int(400, S_HEIGHT-150));
		m_HP = m_MaxHP;
	}

	if (m_Invulnerable > 0)
		m_Invulnerable -= dt;


	//enum m_Sequences{IDLE, ATTACKA, ATTACKB, ATTACKC, DEATH, STEPPING, FANFARE, HIT};

	if (m_CurrentTime > m_Time[m_Sequence])
	{
		if (m_Sequence != DEATH)
			m_CurrentTime = 0;
		if (m_Sequence == ATTACKA || m_Sequence == ATTACKB)
			m_Sequence = IDLE;
	}
	m_CurrentFrame = m_CurrentTime / m_Time[m_Sequence] * (m_Frames[m_Sequence]);
	if (m_Sequence == DEATH)
	{
		if (m_CurrentFrame > m_Frames[m_Sequence])
			m_CurrentFrame = m_Frames[m_Sequence];
	}
	else
	{
		for (unsigned int i = 0; i < powerups.size(); ++i)
		{
			if (powerups[i]->GetRect().Intersect(&GetRect()))
			{
				powerups[i]->GetEffect(this);
				delete powerups[i];
				powerups.erase(powerups.begin() + i);
			}
		}
	}
	//if (m_CurrentFrame > m_Frames[m_Sequence])
	//	m_CurrentFrame = m_Frames[m_Sequence];

}

int Player::GetHit(int damage, short type)
{
	if (m_Sequence == DEATH || m_Invulnerable > 0)
		return 0;
	m_HP -= damage;

	if (m_HP <= 0)
	{
		Die();
		m_Sequence = DEATH;
		m_CurrentTime = 0;
		m_HP = 0;
		m_Cooldown = 5;
		return 1;
	}

	return 0;
}

void Player::Move(int magnitude_x, int magnitude_y, float dt)
{
	if (m_Sequence == DEATH)
		return;

	float magnitude = sqrt((double)magnitude_x * magnitude_x + magnitude_y * magnitude_y);
	float normX = magnitude_x / magnitude;
	float normY = magnitude_y / magnitude;
	
	float mx = normX * m_MaxVelocity * magnitude/32767;
	float my = normY * m_MaxVelocity * magnitude/32767;

	if (magnitude_x > 7000 || magnitude_x < -7000)
	{
		m_Angle = atan2((double)-my, (double)mx);
		if (magnitude_x > 1000)
			m_FlipX = false;
		else
			m_FlipX = true;
		MoveEx(dt, mx, -my);
		if (m_Sequence == IDLE)
		{
			m_Sequence = STEPPING;
			m_CurrentTime = 0;
			//m_CurrentFrame = 0;
		}
	}
	else if (magnitude_y > 7000 || magnitude_y < -7000)
	{
		m_Angle = atan2((double)-my, (double)mx);
		MoveEx(dt, mx, -my);
		if (m_Sequence == IDLE)
		{
			m_Sequence = STEPPING;
			m_CurrentTime = 0;
			//m_CurrentFrame = 0;
		}
	}
	else
	{
		if (m_Sequence == STEPPING)
			m_Sequence = IDLE;
		//m_CurrentTime = 0;
	}

	m_Angle = atan2((double)-my, (double)mx);
}

void Player::ResetPosition (float x, float y)
{
	m_X = x;
	m_Y = y;
}

void Player::AttackA()
{
	if (m_Sequence == DEATH)
		return;

	if (m_Cooldown <= 0 && (m_Sequence == IDLE || m_Sequence == STEPPING))
	{
		//hge->Effect_Play(punch);
		m_Cooldown = m_CooldownA + m_Time[ATTACKA];
		m_Sequence = ATTACKA;
		m_CurrentTime = 0;
	}
	else
		return;

	//m_Rotation = m_Angle;
	hgeRectExt temp = CreateTargetBox(m_W/2 * cos(m_Angle), m_H/2 * sin(m_Angle), m_W, m_H, false);

	if (DEBUG)
	{
		temp.SetLifespan(3);
		tempBoundingBoxes.push_back(temp);
	}
	//m_Rotation = 0;

	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (temp.Intersect(&enemies[i]->GetRect() ) )
		{
			int temp = enemies[i]->GetHit(m_DamageC, 0);
			if (temp > 0)
			{
				m_Kills++;
				m_Score += temp;
			}
		}
	}

	//std::cout << "Attack\n";
}

void Player::AttackB()
{
	if (m_Sequence == DEATH)
		return;

	if (m_Cooldown <= 0 && (m_Sequence == IDLE || m_Sequence == STEPPING))
	{
		m_Cooldown = m_CooldownB + m_Time[ATTACKB];
		m_Sequence = ATTACKB;
		m_CurrentFrame = 0;
		m_CurrentTime = 0;
	}
	else return;

	//std::cout << "Magx " << m_MagX << " Magy " << m_MagY << '\n';
	Bullet * temp = new Bullet("bullet.png", m_X, m_Y, 20, 20, 400, m_Angle, m_DamageB, this);
	bullets.push_back(temp);


}

void Player::AttackC()
{
	if (m_Sequence == DEATH)
		return;

	if (m_Cooldown <= 0 && (m_Sequence == IDLE || m_Sequence == STEPPING))
	{
		//hge->Effect_Play(punch);
		m_Cooldown = m_CooldownC + m_Time[ATTACKC];
		m_Sequence = ATTACKA;
		m_CurrentTime = 0;
	}
	else
		return;

	//m_Rotation = m_Angle;
	hgeRectExt temp = CreateTargetBox(m_W/2, m_H/2, m_W*4, m_H*4, false);
	if (DEBUG)
	{
		temp.SetLifespan(3);
		tempBoundingBoxes.push_back(temp);
	}
	//m_Rotation = 0;

	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (temp.Intersect(&enemies[i]->GetRect() ) )
		{
			int temp = enemies[i]->GetHit(m_DamageC, 0);
			if (temp > 0)
			{
				m_Kills++;
				m_Score += temp;
			}
		}
	}
}

