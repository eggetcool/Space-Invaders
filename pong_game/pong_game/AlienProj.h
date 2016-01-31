#pragma once

#include "IEntity.h"
class Keyboard;

class AlienProj : public IEntity
{
public:
	AlienProj(Sprite* p_pxSprite, float, float);
	~AlienProj();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	bool IsActive();
	EENTITYTYPE GetType();
	void SetVisible(bool p_bValue);
	void Activate();
	void Deactivate();
	void SetPosition(float p_fX, float p_fY);

	float m_fX;

private:
	AlienProj() {};
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	Keyboard* m_pxKeyboard;
	int random;
	float m_fflightSpeed;
	float m_fSpeed;
	float m_fDirY;
	float m_fDirX;
	float m_fY;
	float m_fTimer;
	int m_iScreenWidth;
	int m_iScreenHeight;
	bool m_bVisible;
	bool m_bActive;
};