#include "stdafx.h"
#include "Sprite.h"
#include "AlienProj.h"
#include "Alien.h"
#include "Collider.h"
#include <Windows.h>
#include <cstdlib>
#include <ctime>

AlienProj::AlienProj(Sprite* p_pxSprite, float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fflightSpeed = 0.0f;
	m_fSpeed = 0.0f;
	m_fDirY = 0.0f;
	m_fX = p_fX;
	m_fY = p_fY;
	srand(time(0));
	m_bVisible = true;
	m_bActive = false;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
}

AlienProj::~AlienProj()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void AlienProj::Update(float p_fDeltaTime)
{
	random = 1 + (rand() % 3000);
	if (random == 1)
	{
		std::cout << random << std::endl;
	}
	
	if (m_bActive)
	{
		m_fY -= m_fDirY * m_fSpeed * p_fDeltaTime;
		m_pxCollider->Refresh();
	}
	else
	{
		if (random == 1)
		{
			Activate();
		}
	}

	
}

Sprite* AlienProj::GetSprite()
{
	return m_pxSprite;
}

Collider* AlienProj::GetCollider()
{
	return m_pxCollider;
}

float AlienProj::GetX()
{
	return m_fX;
}

float AlienProj::GetY()
{
	return m_fY;
}

bool AlienProj::IsVisible()
{
	return m_bVisible;
}

bool AlienProj::IsActive()
{
	return m_bActive;
}


EENTITYTYPE AlienProj::GetType()
{
	if (m_bActive)
	{
		return EENTITYTYPE::INFLIGHT;
	}
	else
	{
		return EENTITYTYPE::WAITING;
	}
}


void AlienProj::SetVisible(bool p_bValue)
{
	m_bVisible = p_bValue;
}

void AlienProj::Activate()
{
	m_bActive = true;
	m_fSpeed = 100;
	m_fDirY = -2.0f;
}

void AlienProj::Deactivate()
{
	m_bActive = false;
	m_fflightSpeed = 0;
	m_fDirY = 0.0f;
}

void AlienProj::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider->Refresh();
}
