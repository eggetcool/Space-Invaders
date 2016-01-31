#include "stdafx.h"
#include "DrawManager.h"
#include "Sprite.h"

DrawManager::DrawManager()
{

}

DrawManager::~DrawManager()
{

}

bool DrawManager::Initialize(int p_iWidth, int p_iHeight)
{
	m_pxWindow = SDL_CreateWindow("AntonsArsel",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		p_iWidth, p_iHeight, SDL_WINDOW_OPENGL);

	if (m_pxWindow == nullptr)
	{
		return false;
	}

	m_pxRenderer = SDL_CreateRenderer(m_pxWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pxRenderer == nullptr)
	{
		const char* error = SDL_GetError();
		return false;
	}

	SDL_SetRenderDrawColor(m_pxRenderer, 0x00, 0x00, 0x00, 0xff);

	return true;
}

void DrawManager::Shutdown()
{
	SDL_DestroyRenderer(m_pxRenderer);
	SDL_DestroyWindow(m_pxWindow);

}

void DrawManager::Clear()
{
	SDL_RenderClear(m_pxRenderer);
}

void DrawManager::Present()
{
	SDL_RenderPresent(m_pxRenderer);
}

void DrawManager::Draw(Sprite* p_pxSprite, int p_iX, int p_iY)
{
	SDL_Rect rect = { p_iX, p_iY, p_pxSprite->GetRegion()->w, p_pxSprite->GetRegion()->h };


	SDL_RenderCopy(m_pxRenderer, p_pxSprite->GetTexture(), p_pxSprite->GetRegion(), &rect);
}

SDL_Renderer* DrawManager::GetRenderer()
{
	return m_pxRenderer;
}
