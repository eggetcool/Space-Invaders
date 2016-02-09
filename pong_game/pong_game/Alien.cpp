#include "stdafx.h"
#include "Alien.h"
#include "Sprite.h"
#include "Collider.h"
#include "AlienProj.h"

Alien::Alien(Sprite* p_pxSprite, float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_fDirX = 1.0f;
	m_fSpeed = 70;
	
	m_pxCollider = new Collider(
		p_pxSprite->GetRegion()->w,
		p_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();
}

Alien::~Alien()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Alien::Update(float p_fDeltaTime)
{
	m_fX += m_fDirX * p_fDeltaTime * m_fSpeed;
	m_pxCollider->Refresh();
}

Sprite* Alien::GetSprite()
{
	return m_pxSprite;
}

Collider* Alien::GetCollider()
{
	return m_pxCollider;
}

float Alien::GetX()
{
	return m_fX;
}

float Alien::GetY()
{
	return m_fY;
}

bool Alien::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Alien::GetType()
{
	return EENTITYTYPE::ENTITY_ALIEN;
}

void Alien::ReverseDirectionX()
{
	m_fDirX *= -1;
	m_fY += 10.0f;
}

void Alien::SetVisible(bool p_bValue)
{
	m_bVisible = p_bValue;
}