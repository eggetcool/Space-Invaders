#pragma once

class Collider;

class CollisionManager
{
public:
	static bool Check(Collider* p_pxLeft, Collider* p_pxRight, 
		int& p_iOverlapX, int& p_iOverlapY);
};