#include "stdafx.h"
#include "StateManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "EndState.h"
#include "LoseText.h"
#include "Sprite.h"
#include "Keyboard.h"

EndState::EndState(System& p_pxSystem)
{
	m_xSystem = p_pxSystem;
	m_pxLosetext = nullptr;
}

EndState::~EndState()
{
}

void EndState::Enter()
{
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 92, 0, 76, 21);

	m_pxLosetext = new LoseText(xSprite, m_xSystem.m_iScreenWidth / 2 - 36,
		m_xSystem.m_iScreenHeight / 2);
}

void EndState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxLosetext->GetSprite());
	delete m_pxLosetext;
	m_pxLosetext = nullptr;
}

bool EndState::Update(float p_fDeltaTime)
{
	return true;
}

void EndState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxLosetext->GetSprite(), m_pxLosetext->GetX(), m_pxLosetext->GetY());
}

IState* EndState::NextState()
{
	return nullptr;
}