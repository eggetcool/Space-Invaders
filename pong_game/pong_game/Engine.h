#pragma once

class DrawManager;
class StateManager;
class Keyboard;
class SpriteManager;


class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Update();
	void HandleEvents();

private:
	
	int screen = 0;
	bool m_bRunning;
	Keyboard* m_pxKeyboard;
	DrawManager* m_pxDrawManager;
	StateManager* m_pxStateManager;
	SpriteManager* m_pxSpriteManager;
};