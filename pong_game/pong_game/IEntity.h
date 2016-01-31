#pragma once

enum EENTITYTYPE
{
	ENTITY_TEXT,
	ENTITY_PLAYER,
	ENTITY_PROJECTILE,
	ENTITY_ALIEN,
	WAITING,
	INFLIGHT,
	COVER
};

class Sprite;
class Collider;

class IEntity 
{
public:
	~IEntity() {};
	virtual void Update(float p_fDeltaTime) = 0;
	virtual Sprite* GetSprite() = 0; // Can return nullptr if there is no sprite
	virtual Collider* GetCollider() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
};