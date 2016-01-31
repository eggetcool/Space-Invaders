#include "stdafx.h"
#include "LoseText.h"
#include "Collider.h"

LoseText::LoseText(Sprite* p_pxSprite, float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
}

LoseText::~LoseText()
{

}

void LoseText::Update(float p_fDeltaTime)
{

}

float LoseText::GetX()
{
	return m_fX;
}

float LoseText::GetY()
{
	return m_fY;
}

Sprite* LoseText::GetSprite()
{
	return m_pxSprite;
}

Collider* LoseText::GetCollider()
{
	return m_pxCollider;
}
