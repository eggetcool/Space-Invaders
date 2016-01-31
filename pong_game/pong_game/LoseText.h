#pragma once
#include "IEntity.h"

class LoseText : public IEntity
{
public:
	LoseText(Sprite* p_pxSprite, float p_fX, float p_fY);
	~LoseText();
	void Update(float p_fDeltaTime);
	float GetX();
	float GetY();
	Sprite* GetSprite();
	Collider* GetCollider();
	
private:
	
	float m_fX;
	float m_fY;
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	//
	bool IsVisible() { return true; };
	EENTITYTYPE GetType() { return EENTITYTYPE::ENTITY_TEXT; };
}; 
