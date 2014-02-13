#include "fe/GameHud.h"

using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
GameHud::GameHud(const Vector2f& size) :
	m_Player1Name("PLAYER 1", GameConstants::HudFont, GameConstants::HudPlayerNameTextSize),
	m_Player2Name("PLAYER 2", GameConstants::HudFont, GameConstants::HudPlayerNameTextSize),
	m_Scoreboard("0 - 0", 	  GameConstants::HudFont, GameConstants::HudScoreboardTextSize),
	m_Background(size)
{
	m_Background.setFillColor(GameConstants::HudBackgroundColor);
	m_Player1Name.setColor(GameConstants::HudPlayerNameColor);
	m_Player2Name.setColor(GameConstants::HudPlayerNameColor);
	m_Scoreboard.setColor(GameConstants::HudScoreboardColor);

	auto lbounds = m_Player1Name.getLocalBounds();

	m_Player1Name.setOrigin(lbounds.left + lbounds.width  * 0.5,
							lbounds.top  + lbounds.height * 0.5);

	lbounds = m_Player2Name.getLocalBounds();
	m_Player2Name.setOrigin(lbounds.left + lbounds.width  * 0.5,
							lbounds.top  + lbounds.height * 0.5);

	lbounds = m_Scoreboard.getLocalBounds();
	m_Scoreboard.setOrigin(lbounds.left + lbounds.width  * 0.5,
						   lbounds.top  + lbounds.height * 0.5);

	m_Background.setPosition(0, 0);
	m_Player1Name.setPosition(m_Player1Name.getLocalBounds().width * 0.5, size.y * 0.5);
	m_Player2Name.setPosition(size.x - m_Player2Name.getLocalBounds().width * 0.5, size.y * 0.5);
	m_Scoreboard.setPosition(size.x * 0.5, size.y * 0.5);
}

GameHud::~GameHud()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void GameHud::Draw(RenderWindow& window) const
{
	window.draw(m_Background);
	window.draw(m_Player1Name);
	window.draw(m_Player2Name);
	window.draw(m_Scoreboard);
}

}
