#include "stdafx.h"
#include "Cover.h"
#include "Sprite.h"
#include "Collider.h"

Cover::Cover(Sprite* p_pxSprite, float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider = new Collider(
		p_pxSprite->GetRegion()->w,
		p_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();
}

Cover::~Cover()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Cover::Update(float p_fDeltaTime)
{

}

Sprite* Cover::GetSprite()
{
	return m_pxSprite;
}

Collider* Cover::GetCollider()
{
	return m_pxCollider;
}

float Cover::GetX()
{
	return m_fX;
}

float Cover::GetY()
{
	return m_fY;
}

bool Cover::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Cover::GetType()
{
	return EENTITYTYPE::COVER;
}

void Cover::SetVisible(bool p_bValue)
{
	m_bVisible = p_bValue;
}
