#ifndef __GAME_HUD_H__
#define __GAME_HUD_H__

#include <SFML/Graphics.hpp>
#include "fe/GameConstants.h"

namespace fe
{

class GameHud
{
private:
	sf::Text m_Player1Name;
	sf::Text m_Player2Name;
	sf::Text m_Scoreboard;

	sf::RectangleShape m_Background;

public:
	GameHud(const sf::Vector2f& size);
	GameHud(const GameHud& toCopy);
	GameHud& operator=(const GameHud& toCopy);
	~GameHud();

	void Draw(sf::RenderWindow& window) const;
};

}

#endif
