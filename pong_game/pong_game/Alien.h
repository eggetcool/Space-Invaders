#pragma once
#include "IEntity.h"
class AlienProj;

class Alien : public IEntity
{
public:
	Alien(Sprite* p_pxSprite, float p_fX, float p_fY);
	~Alien();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();
	void ReverseDirectionX();
	void SetVisible(bool p_bValue);
	float m_fX;	
	float m_fDirX;
	float m_fSpeed;

private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	AlienProj* m_pxAlienProj;
	float m_fY;
	bool m_bVisible = true;
	bool alienprojActive = false;
};