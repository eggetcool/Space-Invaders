#pragma once
#include "IEntity.h"

class Cover : public IEntity
{
public:
	Cover(Sprite*, float, float);
	~Cover();
	void Update(float);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();
	void SetVisible(bool);
	
private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	float m_fX;
	float m_fY;
	bool m_bVisible = true;
};