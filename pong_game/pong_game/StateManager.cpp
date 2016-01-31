#include "stdafx.h"
#include "StateManager.h"
#include "IState.h"

StateManager::StateManager()
{
	m_pxCurrentSate = nullptr;
	m_iLastTick = SDL_GetTicks();

}

StateManager::~StateManager()
{
	if (m_pxCurrentSate != nullptr)
	{
		m_pxCurrentSate->Exit();
		delete m_pxCurrentSate;
		m_pxCurrentSate = nullptr;

	}
}

bool StateManager::Update()
{
	float f_DeltaTime = (SDL_GetTicks() - m_iLastTick) * 0.001f;

	if (m_pxCurrentSate != nullptr)
	{
		if (m_pxCurrentSate->Update(f_DeltaTime) == false)
		{
			SetState(m_pxCurrentSate->NextState());
		}
	}

	m_iLastTick = SDL_GetTicks();
	return true;
}

void StateManager::Draw()
{
	if (m_pxCurrentSate != nullptr)
	{
		m_pxCurrentSate->Draw();
	}
}

void StateManager::SetState(IState* p_pxState)
{
	if (m_pxCurrentSate != nullptr)
	{
		m_pxCurrentSate->Exit();
		delete m_pxCurrentSate;
		m_pxCurrentSate = nullptr;
	}

	m_pxCurrentSate = p_pxState;
	m_pxCurrentSate->Enter();
}


