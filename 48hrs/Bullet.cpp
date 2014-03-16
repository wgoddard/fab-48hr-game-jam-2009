#include "Bullet.h"

Bullet::Bullet(const char filename[], int x, int y, int w, int h, int velocity, double angle, int damage, Entity * parent) : Entity(filename, x, y, w, h)
{
	m_Damage = damage;
	m_Velocity = velocity;
	m_Angle = angle;
	m_Alive = true;
	m_Parent = parent;

	if (m_Angle > M_PI)
		m_FlipX = true;

	//std::cout << "particles texture: " << particles->GetTexture() << '\n';
	par = new hgeParticleSystem("particle5.psi", particles);
	particles->SetHotSpot(16,16);
	particles->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_ZWRITE);
	particles->SetZ(0.9);
	//particles->SetColor(particles->GetColor() | 0xFF000000);
	//particles->SetBlendMode(BLEND_ALPHABLEND );
	par->MoveTo(m_X,m_Y);
	par->Fire();
}

Bullet::~Bullet(void)
{
	delete par;
}

void Bullet::Render()
{
	//m_Sprite->Render(m_X, m_Y);
	if (DEBUG)
		RenderBoundingBox();
	par->Render();

	//std::cout << par->Get
}

void Bullet::Update(const float &dt)
{
	m_HasMoved = true;
	m_X += m_Velocity * cos(m_Angle) * dt;
	m_Y += m_Velocity * sin(m_Angle) * dt;
	par->MoveTo(m_X,m_Y);
	par->Update(dt);
}

bool Bullet::IsAlive()
{
	if (m_X > S_WIDTH || m_X < 0)
		return false;
	if (m_Y > S_HEIGHT || m_Y < 0)
		return false;
	return m_Alive;
}