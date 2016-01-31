#include "stdafx.h"
#include "Engine.h"
#include "Keyboard.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "IState.h"
#include "GameState.h"
#include "EndState.h"


const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;

Engine::Engine()
{
	m_bRunning = false;
	m_pxKeyboard = nullptr;
	m_pxStateManager = nullptr;
	m_pxDrawManager = nullptr;
	m_pxSpriteManager = nullptr;
}

Engine::~Engine()
{

}

bool Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	m_pxDrawManager = new DrawManager();
	if (m_pxDrawManager->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT) == false)
	{
		return false;
	}

	m_pxKeyboard = new Keyboard();
	
	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();
	System system;
	system.m_iScreenHeight = WINDOW_HEIGHT;
	system.m_iScreenWidth = WINDOW_WIDTH;
	system.m_pxKeyboard = m_pxKeyboard;
	system.m_pxDrawManager = m_pxDrawManager;
	system.m_pxSpriteManager = m_pxSpriteManager;
	
	//Endstate ändra så dom ligger i .h
	GameState* xGameState = new GameState(system);
	EndState* xEndState = new EndState(system);
	m_pxStateManager->SetState(xGameState);


	m_bRunning = true;
	return true;

}

void Engine::Shutdown()
{
	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;

	delete m_pxKeyboard;
	m_pxKeyboard = nullptr;

	m_pxDrawManager->Shutdown();
	delete m_pxDrawManager;
	m_pxDrawManager = nullptr;

	SDL_Quit();
}

void Engine::Update()
{
	while (m_bRunning && m_pxStateManager->Update() >= 0)
	{
		HandleEvents();
		m_pxDrawManager->Clear();
		if (m_pxStateManager->Update() == false)
		{
			m_bRunning = false;
		}
		m_pxStateManager->Draw();
		m_pxDrawManager->Present();
		SDL_Delay(10);

	}
}

void Engine::HandleEvents()
{
	//InputManager
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{
		if (xEvent.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else if (xEvent.type == SDL_KEYDOWN)
		{
			m_pxKeyboard->SetButton(xEvent.button.button, true);
		}
		else if (xEvent.type == SDL_KEYUP)
		{
			m_pxKeyboard->SetButton(xEvent.button.button, false);
		}
	}
}