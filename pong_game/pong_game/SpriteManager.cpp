#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"

SpriteManager::SpriteManager(SDL_Renderer* p_pxRenderer)
{
	m_pxRenderer = p_pxRenderer;
}

SpriteManager::~SpriteManager()
{
	{
		auto it = m_apxSprites.begin();
		while (it != m_apxSprites.end())
		{
			delete (*it);
			it++;
		}
		m_apxSprites.clear();
	}
	{
		auto it = m_apxTextures.begin();
		while (it != m_apxTextures.end())
		{
			SDL_DestroyTexture(it->second);
			it++;
		}
		m_apxTextures.clear();
	}
}

Sprite* SpriteManager::CreateSprite(const std::string& p_sFilepath, int p_iX, int p_iY, int p_iW, int p_iH)
{
	auto it = m_apxTextures.find(p_sFilepath);
	if (it == m_apxTextures.end())
	{
		SDL_Surface* xSurface = SDL_LoadBMP(p_sFilepath.c_str());
		SDL_Texture* xTexture = SDL_CreateTextureFromSurface(m_pxRenderer, xSurface);
		SDL_FreeSurface(xSurface);
		m_apxTextures.insert(std::pair<std::string, SDL_Texture*>(p_sFilepath, xTexture));
		it = m_apxTextures.find(p_sFilepath);
	}

	Sprite* xSprite = new Sprite(it->second, p_iX, p_iY, p_iW, p_iH);
	m_apxSprites.push_back(xSprite);
	return xSprite;
}

void SpriteManager::DestroySprite(Sprite* p_pxSprite)
{
	auto it = m_apxSprites.begin();
	while (it != m_apxSprites.end())
	{
		if ((*it) == p_pxSprite)
		{
			delete (*it);
			m_apxSprites.erase(it);
			return;
		}
		it++;
	}
}


