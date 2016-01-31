#include "stdafx.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Keyboard.h"
#include "Sprite.h"
#include "PlayerShip.h"
#include "Projectile.h"
#include "AlienProj.h"
#include "Alien.h"
#include "AlienRect.h"
#include "CollisionManager.h"
#include "EndState.h"
#include "Cover.h"
#include "LoseText.h"

//Meny, score, end, victory, resize av hitbox

GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayerShip = nullptr;
	m_pxProjectile = nullptr;
	m_pxAlienRect = nullptr;
	m_pxStateManager = nullptr;
	m_pxAlienProj = nullptr;
	m_pxCover = nullptr;
	m_pxMusic = nullptr;
	m_pxShoot = nullptr;
	m_pxLoseText = nullptr;
	Mix_Init(MIX_INIT_MP3);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}

	m_pxShoot = Mix_LoadWAV("../assets/plop.wav");
	if (m_pxShoot == nullptr)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}
}


GameState::~GameState()
{
	Mix_FreeChunk(m_pxShoot);
	m_pxShoot = nullptr;
}

void GameState::Enter()
{
	////////////////////
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 0, 0, 21, 8);
	SDL_Rect* xRect = xSprite->GetRegion();
	int iHeight = xRect->h;

	//Playership
	m_pxPlayerShip = new PlayerShip(m_xSystem.m_pxKeyboard, xSprite, m_xSystem.m_iScreenWidth / 2, 
		m_xSystem.m_iScreenHeight - 20 - iHeight, m_xSystem.m_iScreenWidth);

	//Player projectile
	m_pxProjectile = new Projectile(m_xSystem.m_pxKeyboard,
		m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 0, 10, 1, 4),
		m_xSystem.m_iScreenWidth,
		m_xSystem.m_iScreenHeight);

	
	//Invaders
	SDL_Rect blockCoords[] = 
	{
		{23, 0, 21, 8},
		{46, 0, 21, 8},
		{69, 0, 21, 8}
	};
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SDL_Rect& rect = blockCoords[j % 3];
			Alien* pxAlien = new Alien(
				m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", rect.x, rect.y, rect.w, rect.h),
				10 + i * 50.0f,
				10 + j * 20);
			m_apxAlien.push_back(pxAlien);
		}
	}

	//Alien rektangel hitbox.
	auto rectit = m_apxAlien.begin();
	auto endrect = m_apxAlien.rbegin();
	int x = (*rectit)->GetX();
	int y = (*rectit)->GetY();
	int w = (*endrect)->GetX() + (*endrect)->GetSprite()->GetRegion()->w;
	int h = (*endrect)->GetY() + (*endrect)->GetSprite()->GetRegion()->h;
	m_pxAlienRect = new AlienRect(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 
		0, 40, w, h), x, y, w, h);
	
	//Alien skott
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_pxAlienProj = new AlienProj(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp",
				3, 9, 2, 6), 
				10 + i * 50.0f,
				10 + j *20);
			m_apxAlienP.push_back(m_pxAlienProj);
		}
	}

	//Skydd
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int x = 0; x < 7; x++)
			{
				m_pxCover = new Cover(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp",
					0, 27, 5, 9),
					100 + (i*125.0f) + x*6,
                    400 + j * 9.0f);
				m_apxCover.push_back(m_pxCover);
			}
			
		}
	}
	Sprite* xSpriteText = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 92, 0, 76, 21);

	m_pxLoseText = new LoseText(xSpriteText, m_xSystem.m_iScreenWidth / 2,
		m_xSystem.m_iScreenHeight / 2);
}

void GameState::Exit()
{
	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxLoseText->GetSprite());
	delete m_pxLoseText;
	m_pxLoseText = nullptr;

	auto covit = m_apxCover.begin();
	while (covit != m_apxCover.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*covit)->GetSprite());
		delete (*covit);
		covit++;
	}

	//Skriv om denna så det blir rätt ordning
	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxPlayerShip->GetSprite());
	delete m_pxPlayerShip;
	m_pxPlayerShip = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxProjectile->GetSprite());
	delete m_pxProjectile;
	m_pxProjectile = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxAlienProj->GetSprite());
	delete m_pxAlienProj;
	m_pxAlienProj = nullptr;

	auto it = m_apxAlien.begin();
	while (it != m_apxAlien.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it)->GetSprite());
		delete *it;
		it++;
	}
	m_apxAlien.clear();

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxAlienRect->GetSprite());
	delete m_pxAlienRect;
	m_pxAlienRect = nullptr;
	
	//Temp
	auto projit = m_apxAlienP.begin();
	while (projit != m_apxAlienP.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*projit)->GetSprite());
		delete *projit;
		projit++;
	}
	m_apxAlienP.clear();
}

bool GameState::Update(float p_fDeltaTime)
{
	m_pxPlayerShip->Update(p_fDeltaTime);
	m_pxProjectile->Update(p_fDeltaTime);
	m_pxAlienRect->Update(p_fDeltaTime);
	if (m_pxProjectile->IsActive() == false)
	{
		m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2 - m_pxProjectile->GetSprite()->GetRegion()->w / 2,
			m_pxPlayerShip->GetY() + m_pxPlayerShip->GetSprite()->GetRegion()->h / 2 - m_pxProjectile->GetSprite()->GetRegion()->h / 2);
	}
	if (m_pxProjectile->GetY() < 0)
	{
		m_pxProjectile->Deactivate();
		m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2,
			m_pxPlayerShip->GetY());
	}	
	//Kod för att få aliens att skjuta.
	auto projit = m_apxAlienP.begin();
	auto it = m_apxAlien.begin();
	while (it != m_apxAlien.end())
	{
		(*it)->Update(p_fDeltaTime);
		(*projit)->Update(p_fDeltaTime);
		if ((*it)->IsVisible())
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*it)->GetSprite(),
				(*it)->GetX(),
				(*it)->GetY());
		}
		if ((*projit)->IsVisible() && (*it)->IsVisible())
		{
			
			m_xSystem.m_pxDrawManager->Draw(
				(*projit)->GetSprite(),
				(*projit)->GetX(),
				(*projit)->GetY());
		}
		if ((*projit)->IsActive() == false)
		{
			(*projit)->SetPosition((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w / 2, (*it)->GetY());
		}
		if ((*projit)->GetY() > m_xSystem.m_iScreenHeight)
		{
			(*projit)->Deactivate();
			(*projit)->SetPosition((*it)->GetX() + (*it)->GetSprite()->GetRegion()->w, (*it)->GetY() + (*it)->GetSprite()->GetRegion()->h);
		}
		projit++;
		it++;
	}
	isFalse = false;
	//Satt med detta problem i 1.5 veckor. Lyckan.... =^.^=( . . )~~~~
	if (m_pxAlienRect->GetX() > m_xSystem.m_iScreenWidth - m_pxAlienRect->GetW() && isFalse == false)
	{
		auto it = m_apxAlien.begin();
		while (it != m_apxAlien.end())
		{
			(*it)->Update(p_fDeltaTime);
			(*it)->ReverseDirectionX();
			if ((*it)->IsVisible())
			{
				m_xSystem.m_pxDrawManager->Draw(
					(*it)->GetSprite(),
					(*it)->GetX(),
					(*it)->GetY());
			}
			it++;
		}
		isFalse = true;
		m_pxAlienRect->ReverseDirection();
	}
	isFalse = false;
	if (m_pxAlienRect->GetX() < 0 && isFalse == false)
	{
		auto it = m_apxAlien.begin();
		while (it != m_apxAlien.end())
		{
			(*it)->Update(p_fDeltaTime);
			(*it)->ReverseDirectionX();
			if ((*it)->IsVisible())
			{
				m_xSystem.m_pxDrawManager->Draw(
					(*it)->GetSprite(),
					(*it)->GetX(),
					(*it)->GetY());
			}
			it++;
		}
		isFalse = true;
		m_pxAlienRect->ReverseDirection();
	}

	//Endstate
	/*
	if (m_pxAlienRect->GetY() + m_pxAlienRect->GetH() > m_xSystem.m_iScreenHeight - 100)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxLoseText->GetSprite(), m_pxLoseText->GetX(), m_pxLoseText->GetY());
		std::cout << "Förlust" << std::endl;
		SDL_Delay(100);
		return (-1);
	}*/
	CheckCollision();
	return true;
}

void GameState::Draw()
{
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayerShip->GetSprite(), m_pxPlayerShip->GetX(), m_pxPlayerShip->GetY());
	m_xSystem.m_pxDrawManager->Draw(m_pxProjectile->GetSprite(), m_pxProjectile->GetX(), m_pxProjectile->GetY());
	m_xSystem.m_pxDrawManager->Draw(m_pxAlienRect->GetSprite(), m_pxAlienRect->GetX(), m_pxAlienRect->GetY());
	m_xSystem.m_pxDrawManager->Draw(m_pxAlienProj->GetSprite(), m_pxAlienProj->GetX(), m_pxAlienProj->GetY());

	auto covit = m_apxCover.begin();
	while (covit != m_apxCover.end())
	{
		if ((*covit)->IsVisible())
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*covit)->GetSprite(),
				(*covit)->GetX(),
				(*covit)->GetY());
		}
		covit++;
	}

	auto it = m_apxAlien.begin();
	while (it != m_apxAlien.end())
	{
		if ((*it)->IsVisible())
		{
			m_xSystem.m_pxDrawManager->Draw(
				(*it)->GetSprite(),
				(*it)->GetX(),
				(*it)->GetY());
		}
		it++;
	}
}

IState* GameState::NextState()
{
	//kanske ha switch för tre olika cases, if gamestate.update return false byt till ett annat state.
	return nullptr;
}

void GameState::CheckCollision()
{
	int iOverlapX = 0;
	int iOverlapY = 0;
	auto projit = m_apxAlienP.begin();
	while (projit != m_apxAlienP.end())
	{
		if (CollisionManager::Check((*projit)->GetCollider(), m_pxPlayerShip->GetCollider(), iOverlapX, iOverlapY))
		{
			if (abs(iOverlapX) > abs(iOverlapY))
			{
				(*projit)->Deactivate();
				m_pxPlayerShip->Life(-1);
			}
			else
			{
				(*projit)->Deactivate();
				m_pxPlayerShip->Life(-1);
			}
		}
		
		projit++;
	}

	auto covit = m_apxCover.begin();
	while (covit != m_apxCover.end())
	{
		projit = m_apxAlienP.begin();
		if (CollisionManager::Check((*covit)->GetCollider(), m_pxProjectile->GetCollider(), iOverlapX, iOverlapY))
		{
			if ((*covit)->IsVisible())
			{
				if (abs(iOverlapX) > abs(iOverlapY))
				{
					(*covit)->SetVisible(false);
					m_pxProjectile->Deactivate();
					m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2,
						m_pxPlayerShip->GetY());
				}
				else
				{
					(*covit)->SetVisible(false);
					m_pxProjectile->Deactivate();
					m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2,
						m_pxPlayerShip->GetY());
				}
			}
		}
		while (projit != m_apxAlienP.end())
		{
			if (CollisionManager::Check((*covit)->GetCollider(), (*projit)->GetCollider(), iOverlapX, iOverlapY))
			{
				if ((*covit)->IsVisible())
				{
					if (abs(iOverlapX) > abs(iOverlapY))
					{
						(*projit)->Deactivate();
						(*covit)->SetVisible(false);

					}
					else
					{
						(*projit)->Deactivate();
						(*covit)->SetVisible(false);

					}
				}

			}
			projit++;
		}
		covit++;
	}



	auto it = m_apxAlien.begin();
	while (it != m_apxAlien.end())
	{
		if ((*it)->IsVisible())
		{
			if (CollisionManager::Check((*it)->GetCollider(), m_pxProjectile->GetCollider(), iOverlapX, iOverlapY))
			{
				Mix_PlayChannel(-1, m_pxShoot, 0);

				if (abs(iOverlapX) > abs(iOverlapY))
				{
					//lägg till snabbare aliens relativt till antal.
					m_pxProjectile->Deactivate();
					m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2,
						m_pxPlayerShip->GetY());
					(*it)->SetVisible(false);
				}
				else
				{
					m_pxProjectile->Deactivate();
					m_pxProjectile->SetPosition(m_pxPlayerShip->GetX() + m_pxPlayerShip->GetSprite()->GetRegion()->w / 2,
						m_pxPlayerShip->GetY());
					(*it)->SetVisible(false);
				}
				//kolla storlek på rect och aliens X
				/*auto tempit = m_apxAlien.rbegin();
				while (tempit != m_apxAlien.rend())
				{
					//Fixa, händer inget
					if ((m_pxAlienRect->GetX() + m_pxAlienRect->GetSprite()->GetRegion()->w) > ((*tempit)->GetX() + (*tempit)->GetSprite()->GetRegion()->w) && (*tempit)->IsVisible())
					{
						m_xSystem.m_pxSpriteManager->DestroySprite(m_pxAlienRect->GetSprite());
						delete m_pxAlienRect;

						auto rectit = m_apxAlien.begin();
						auto endrect = m_apxAlien.rbegin();
						int x = (*rectit)->GetX();
						int y = (*rectit)->GetY();
						int w = (*endrect)->GetX() + (*endrect)->GetSprite()->GetRegion()->w;
						int h = (*endrect)->GetY() + (*endrect)->GetSprite()->GetRegion()->h;

						m_pxAlienRect = new AlienRect(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/main.bmp", 0, 40, w, h), x, y, w, h);
					}
					tempit++;
				}*/
			}
		}		
		it++;
	}
}
