#pragma once
class IState;

class StateManager
{
	friend class Engine;
	friend class GameState;
public:
	StateManager();
	~StateManager();
	bool Update();
	void Draw();
private:
	void SetState(IState* p_pxState);
	IState* m_pxCurrentSate;
	int m_iLastTick;
};