#pragma once

class Keyboard;
#include "IEntity.h"


class Projectile :  public IEntity
{
public:
	Projectile(Keyboard* p_pxKeyboard, Sprite* p_pxSprite, 
		int p_iScreenWidth, int p_iScreenHeight);
	~Projectile();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	bool IsActive();
	
	EENTITYTYPE GetType();

	void Activate();
	void Deactivate();
	void SetPosition(float p_fX, float p_fY);
private:
	Projectile() {};
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	Keyboard* m_pxKeyboard;
	float m_fSpeed;
	float m_fDirY;
	float m_fX;
	float m_fY;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bVisible;
	bool m_bActive;
};