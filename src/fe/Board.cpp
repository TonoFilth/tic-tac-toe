#include "fe/Board.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
Board::Board(const Vector2u& boardSize, const Vector2u& squareSize,
		     const Vector2i& position,  const Texture& squareTexture) :
	m_BoardSize(boardSize),
	m_SquareSize(squareSize),
	m_Position(position),
	m_Bounds(position.x - (boardSize.x * 0.5 * squareSize.x),
			 position.y - (boardSize.y * 0.5 * squareSize.y),
			 position.x - (boardSize.x * 0.5 * squareSize.x) + boardSize.x * squareSize.x,
			 position.y - (boardSize.y * 0.5 * squareSize.y) + boardSize.y * squareSize.y)
{
	UI32 curX = m_Bounds.left;
	UI32 curY = m_Bounds.top;
	
	F32 scaleX = squareSize.x / static_cast<F32>(squareTexture.getSize().x);
	F32 scaleY = squareSize.y / static_cast<F32>(squareTexture.getSize().y);
	
	Sprite square(squareTexture);
	square.setScale(scaleX, scaleY);

	for (UI32 i = 0; i < boardSize.x; ++i)
	{
		for (UI32 j = 0; j < boardSize.y; ++j)
		{
			square.setPosition(curX, curY);
			m_Squares.push_back(square);
			curX += squareSize.x;
		}

		curX  = m_Bounds.left;
		curY += squareSize.y;
	}
}

Board::~Board()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool Board::PutChip(UI32 x, UI32 y, const TPlayerID playerId)
{
	if (m_PlayerChipMap.find(playerId) == m_PlayerChipMap.end() ||
		x >= m_BoardSize.x || y >= m_BoardSize.y)
		return false;

	I32 xPos = m_Bounds.left + x * m_SquareSize.x;
	I32 yPos = m_Bounds.top  + y * m_SquareSize.y;
	Sprite* s = &m_PlayerChipMap[playerId];

	xPos += m_SquareSize.x * 0.5 - s->getGlobalBounds().width  * 0.5;
	yPos += m_SquareSize.y * 0.5 - s->getGlobalBounds().height * 0.5;
	
	if (xPos < m_Bounds.left || xPos > m_Bounds.width ||
		yPos < m_Bounds.top  || yPos > m_Bounds.height)
		return false;

	s->setPosition(xPos, yPos);
	m_Chips.push_back(*s);

	return true;
}

void Board::Draw(RenderWindow& window) const
{
	for (auto& square : m_Squares)
		window.draw(square);

	for (auto& chip : m_Chips)
		window.draw(chip);
}

void Board::Reset()
{
	m_Chips.clear();
	m_Movements.clear();
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void Board::SetPlayerChip(TPlayerID id, const Sprite& chipSprite)
{
	m_PlayerChipMap[id] = chipSprite;
}

}
