#pragma once
#include "IState.h"

class Keyboard;
class PlayerShip;
class Projectile;
class Alien;
class AlienProj;
class AlienRect;
class StateManager;
class EndState;
class Cover;
class LoseText;

class GameState : public IState
{
public:
	GameState(System& p_xSystem);
	~GameState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();
	bool Lose();
private:
	void CheckCollision();
	bool isFalse = false;
	bool m_bLose = false;
	System m_xSystem;
	EndState* m_pxEndState;
	Keyboard* m_pxKeyboard;
	StateManager* m_pxStateManager;
	PlayerShip* m_pxPlayerShip;
	Projectile* m_pxProjectile;
	AlienRect* m_pxAlienRect;
	AlienProj* m_pxAlienProj;
	Cover* m_pxCover;
	Mix_Chunk* m_pxShoot;
	Mix_Music* m_pxMusic;
	LoseText* m_pxLoseText;
	std::vector<AlienProj*> m_apxAlienP;
	std::vector<Alien*> m_apxAlien;
	std::vector<Cover*> m_apxCover;
	
};