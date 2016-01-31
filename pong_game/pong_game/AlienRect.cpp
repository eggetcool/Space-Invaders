#include "stdafx.h"
#include "Collider.h"
#include "AlienRect.h"
#include "Sprite.h"

AlienRect::AlienRect(Sprite* p_pxSprite, float p_fX, float p_fY, float p_fW, float p_fH)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_fW = p_fW;
	m_fH = p_fH;
	m_fDirX = 1.0f;
	m_fSpeed = 70;
	alienMovRect.x = p_fX;
	alienMovRect.y = p_fY;
	alienMovRect.w = p_fW;
	alienMovRect.h = p_fH;
	m_pxCollider = new Collider(p_pxSprite->GetRegion()->w, p_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();
}

AlienRect::~AlienRect()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void AlienRect::Update(float p_fDeltaTime)
{
	m_fX += m_fDirX * m_fSpeed * p_fDeltaTime;
	m_pxCollider->Refresh();
}

float AlienRect::GetX()
{
	return m_fX;
}

float AlienRect::GetY()
{
	return m_fY;
}

float AlienRect::GetW()
{
	return m_fW;
}

float AlienRect::GetH()
{
	return m_fH;
}

void AlienRect::ReverseDirection()
{
	m_fDirX *= -1;
	m_fY += 10;
}

bool AlienRect::IsVisible()
{
	return m_bVisible;
}

Collider* AlienRect::GetCollider()
{
	return m_pxCollider;
}

Sprite* AlienRect::GetSprite()
{
	return m_pxSprite;
}
