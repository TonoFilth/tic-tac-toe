#ifndef __BOARD_H__
#define __BOARD_H__

#include <list>

#include "fe/BasicTypes.h"
#include "fe/PlayerTypes.h"

namespace fe
{

//typedef std::vector<std::vector<sf::Sprite> > TSquareBoard;
typedef std::list<sf::Sprite> TSpriteList;

class Board
{
private:
	sf::Vector2u m_BoardSize;
	sf::Vector2u m_SquareSize;
	sf::Vector2i m_Position;
	sf::IntRect  m_Bounds;

	TPlayerChipMap   m_PlayerChipMap;
	TSpriteList      m_Squares;
	TSpriteList      m_Chips;
	TPlayerMovements m_Movements;

public:
	Board(const sf::Vector2u& boardSize, const sf::Vector2u& squareSize,
		  const sf::Vector2i& position,  const sf::Texture& squareTexture);
	Board(const Board& toCopy);
	Board& operator=(const Board& toCopy);
	~Board();

	bool PutChip(UI32 x, UI32 y, const TPlayerID playerId);
	void Draw(sf::RenderWindow& window) const;
	void Reset();

	void SetPlayerChip(TPlayerID id, const sf::Sprite& chipSprite);
};

}

#endif
