#pragma once

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	bool IsButtonDown(int p_iIndex);
	void SetButton(int p_iIndex, bool p_bValue);
private:
	bool m_abButtons[256];
};