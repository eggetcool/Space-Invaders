#pragma once

#include "IEntity.h"
class Keyboard;

class PlayerShip : public IEntity
{
public:
	PlayerShip(Keyboard* p_pxKeyboard, Sprite* p_pxSprite,
		float p_fX, float p_fY, int p_iScreenWidth);
	~PlayerShip();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	void Life(int);
	bool IsVisible();
	EENTITYTYPE GetType();
private:
	PlayerShip() {};
	Keyboard* m_pxKeyboard;
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	
	float m_fX = 0;
	float m_fY;
	int m_iScreenWidth;
	bool m_bVisible;
	int life;
};