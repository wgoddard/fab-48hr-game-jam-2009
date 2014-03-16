#include "Fan.h"
#include "Player.h"
#include "Prince.h"

extern std::vector <Player *> players;
extern std::vector <hgeRectExt> tempBoundingBoxes;
extern Prince * prince;


Fan::Fan(const char filename[], int x, int y, int w, int h, float scalex, float scaley, int hp, int damage, bool isboss) : Enemy(filename, x, y, w, h, scalex, scaley, hp, damage)
{
	m_Target = hge->Random_Int(0, NUMBER_PLAYERS - 1);
	m_Value = 5;
	m_HP = hp;
	m_MaxHP = hp;
	m_Sequence = 0;
	m_Status = NORMAL;
	m_MaxVelocity = 200;

	m_Damage = damage;

	m_CooldownAttack = 1;
	m_Timer = 0;

	//float Time[8] = {1, 1, 1, 1, .6, 0.5, 1, 0.5};
	//int Frames[8] = {3, 6, 6, 6, 3, 3, 3, 3};
	float Time[8] = {1, 1, 1, 1, .6, 0.5, 1, 0.5};
	int Frames[8] = {1, 4, 1, 1, 5, 4, 1, 1};


	for (int i = 0; i < 8; ++i)
	{
		m_Frames[i] = Frames[i];
		m_Time[i] = Time[i];
	}

	//if (isboss)
	//{
	//	int Frames[8] = {1, 10, 1, 1, 10, 10, 1, 1};
	//	for (int i = 0; i < 8; ++i)
	//		m_Frames[i] = Frames[i];
	//}
	m_IsBoss = isboss;
}

Fan::~Fan(void)
{
}

void Fan::AI(float dt)
{
	if (m_Sequence == DEATH)
		return;

	if(m_Target > -1){
		if(!players[m_Target]->IsAlive())
		{
			m_Target = -1;
			if(hge->Random_Int(0, 10) == 1)
			{
				m_Target = -1;
			} else
			{
				for(int i = 0; i < players.size(); ++i){
					if(players[i]->IsAlive()){
						m_Target = i;
						break;
					}
				}
			}
		}
	}

	int targetx, targety, realtargetx;
	if (m_Target > -1 && m_Kills < 1)
	{
		realtargetx = players[m_Target]->GetX();
		targetx = players[m_Target]->GetX()-players[m_Target]->GetW();
		targety = players[m_Target]->GetY();
	}
	else
	{
		realtargetx = prince->GetX();
		targetx = prince->GetX();
		targety = prince->GetY();
	}

	int temp = hge->Random_Int(0, 1);

	m_Angle = atan2(m_Y-targety, m_X-targetx);
	
	if (m_X > realtargetx)
		m_FlipX = true;
	else
		m_FlipX = false;


	//m_Timer -= dt;

	static float xNew, yNew;

	//if (m_Timer <= 0)
	{
		xNew = -cos(m_Angle) * m_MaxVelocity;
		yNew = -sin(m_Angle) * m_MaxVelocity;
		m_TargetBox = CreateTargetBox(m_W/2 * cos(m_Angle), m_H/2 * -sin(m_Angle), m_W/2, m_H/2, true);
		//m_Timer = 1;
	}

	int wobble = 3;
	if (m_IsBoss)
		wobble = 0;
	MoveEx(dt, xNew + wobble * hge->Random_Int(-m_W, m_W), yNew + wobble * hge->Random_Int(-m_H, m_H));
	//MoveEx(dt, -200);

		if(DEBUG)
	{
		m_TargetBox.SetLifespan(3);
		tempBoundingBoxes.push_back(m_TargetBox);
	}

	if (m_Cooldown <= 0)
	{
		int size = players.size();

		for (unsigned int i = 0; i < size; ++i)
		{
			if (m_TargetBox.Intersect(&players[i]->GetRect()))
			{
				m_Sequence = ATTACK;
				m_CurrentTime = 0;
				m_Kills += players[i]->GetHit(m_Damage, 0);
				m_Cooldown += m_CooldownAttack;
			}
		}
		if (m_TargetBox.Intersect(&prince->GetRect()))
		{
			m_Sequence = ATTACK;
			m_CurrentTime = 0;
			m_Cooldown += m_CooldownAttack;
			prince->GetHit(m_Damage, 0);
		}
	}
}