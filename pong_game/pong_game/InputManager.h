#pragma once

class Keyboard;

class InputManager
{
	friend class Engine;

public:
	InputManager();
	~InputManager();
	Keyboard* GetKeyboard();

private:
	void SetKeyboard(int key, bool state);
	Keyboard* m_keyboard;
};