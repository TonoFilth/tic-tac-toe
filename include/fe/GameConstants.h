#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "fe/BasicTypes.h"

namespace fe
{

class GameConstants
{
private:
	static const std::string Player1TextureFile;
	static const std::string Player2TextureFile;
	static const std::string SquareTextureFile;
	
	static bool st_Initialized;

public:
	GameConstants();
	GameConstants(const GameConstants& toCopy);
	GameConstants& operator=(const GameConstants& toCopy);
	~GameConstants();

	static sf::Texture Player1Texture;
	static sf::Texture Player2Texture;
	static sf::Texture SquareTexture;

	static const sf::Vector2u WindowSize;
	static const sf::Vector2u BoardSize;
	static const sf::Vector2u SquareSize;

	static bool Init();
};

}

#endif
