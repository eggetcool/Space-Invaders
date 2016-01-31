#include "stdafx.h"
#include "Projectile.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "PlayerShip.h"
#include "Collider.h"

Projectile::Projectile(Keyboard* p_pxKeyboard, Sprite* p_pxSprite, int p_iScreenWidth, int p_iScreenHeight)
{
	m_pxKeyboard = p_pxKeyboard;
	m_pxSprite = p_pxSprite;
	m_iScreenWidth = p_iScreenWidth;
	m_iScreenHeight = p_iScreenHeight;
	m_fSpeed = 0.0f;
	m_fDirY = 0.0f;
	m_fX = 0.0f;
	m_fY = 0.0f;
	m_bVisible = true;
	m_bActive = false;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
}

Projectile::~Projectile()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Projectile::Update(float p_fDeltaTime)
{
	if (m_bActive)
	{
		m_fY += m_fDirY * m_fSpeed * p_fDeltaTime;
		
		m_pxCollider->Refresh();
	}
	else
	{
		if (m_pxKeyboard->IsButtonDown(82))
		{
			Activate();
		}
	}
}

Sprite* Projectile::GetSprite()
{
	return m_pxSprite;
}

Collider * Projectile::GetCollider()
{
	return m_pxCollider;
}

float Projectile::GetX()
{
	return	m_fX;
}

float Projectile::GetY()
{
	return m_fY;
}

bool Projectile::IsVisible()
{
	return m_bVisible;
}

bool Projectile::IsActive()
{
	return m_bActive;
}

EENTITYTYPE Projectile::GetType()
{
	return EENTITYTYPE::ENTITY_PROJECTILE;
}

void Projectile::Activate()
{
	m_bActive = true;
	m_fSpeed = 300;
	m_fDirY = -2.0f;
}

void Projectile::Deactivate()
{
	m_bActive = false;
	m_fSpeed = 0;
	m_fDirY = 0.0f;
}

void Projectile::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}
