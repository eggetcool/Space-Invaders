#pragma once
#include "IState.h"

class LoseText;
class Keyboard;

class EndState : public IState
{
public:
	EndState(System& p_pxSystem);
	~EndState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();
private:
	bool m_bRunning = true;
	System m_xSystem;
	LoseText* m_pxLosetext;
};