#pragma once
#include "IEntity.h"

class AlienRect : public IEntity
{
public:
	AlienRect(Sprite* p_pxSprite, float p_fX, float p_fY, float p_fW, float p_fH);
	~AlienRect();
	void Update(float p_fDeltaTime);
	float GetX();
	float GetY();
	float GetW();
	float GetH();
	void ReverseDirection();
	bool IsVisible();
	Collider* GetCollider();
	Sprite* GetSprite();

	SDL_Rect alienMovRect;
	float m_fX;
	float m_fY;
	float m_fW;
	float m_fH;
	float m_fDirX;
	float m_fSpeed;
private:
	bool m_bVisible = true;
	Collider* m_pxCollider;
	Sprite* m_pxSprite;
	EENTITYTYPE GetType() {return EENTITYTYPE::ENTITY_ALIEN; };




};