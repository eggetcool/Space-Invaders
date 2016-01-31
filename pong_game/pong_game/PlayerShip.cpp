#include "stdafx.h"
#include "PlayerShip.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "Collider.h"

PlayerShip::PlayerShip(Keyboard* p_pxKeyboard, Sprite* p_pxSprite, float p_fX, float p_fY, int p_iScreenWidth)
{
	m_pxKeyboard = p_pxKeyboard;
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	life = 3;
	m_iScreenWidth = p_iScreenWidth;
	m_bVisible = true;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
}

PlayerShip::~PlayerShip()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void PlayerShip::Update(float p_fDeltaTime)
{
	//Flytta till InputManager
	if (m_pxKeyboard->IsButtonDown(79))
	{
		m_fX += 5;
	}
	if (m_pxKeyboard->IsButtonDown(80))
	{
		m_fX -= 5;
	}
	if (m_fX < 0)
	{
		m_fX = 0;
	}
	if ((m_fX + m_pxSprite->GetRegion()->w) > m_iScreenWidth)
	{
		m_fX = m_iScreenWidth - m_pxSprite->GetRegion()->w;
	}
	//
	m_pxCollider->Refresh();
}

Sprite* PlayerShip::GetSprite()
{
	return m_pxSprite;
}

Collider* PlayerShip::GetCollider()
{
	return m_pxCollider;
}

float PlayerShip::GetX()
{
	return m_fX;
}

float PlayerShip::GetY()
{
	return m_fY;
}

void PlayerShip::Life(int p_iLife)
{
	life += p_iLife;
	std::cout << "Life left: " << life << std::endl;
	if (life < 0)
	{
		std::cout << "you lose" << std::endl;
		return;
	}
}

bool PlayerShip::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE PlayerShip::GetType()
{
	return EENTITYTYPE::ENTITY_PLAYER;
}

