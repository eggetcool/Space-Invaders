#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
	{
		m_abButtons[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

bool Keyboard::IsButtonDown(int p_iIndex)
{
	if (p_iIndex < 0)
	{
		return false;
		
	}
	if (p_iIndex > 255)
	{
		return false;
	}
	
	return m_abButtons[p_iIndex];
}

void Keyboard::SetButton(int p_iIndex, bool p_bValue)
{
	if (p_iIndex < 0)
		return;
	if (p_iIndex > 255)
		return;
	m_abButtons[p_iIndex] = p_bValue;
	//std::cout << p_iIndex << std::endl;
}
