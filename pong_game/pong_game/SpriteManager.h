#pragma once

class Sprite;

class SpriteManager
{
public:
	SpriteManager(SDL_Renderer* p_pxRenderer);
	~SpriteManager();

	Sprite* CreateSprite(const std::string& p_sFilepath,
		int p_iX, int p_iY, int p_iW, int p_iH);
	void DestroySprite(Sprite* p_pxSprite);

private:
	SpriteManager();
	SDL_Renderer* m_pxRenderer;
	std::vector<Sprite*> m_apxSprites;
	std::map<std::string, SDL_Texture*> m_apxTextures;
};