#ifndef __FGAME_H__
#define __FGAME_H__

#include "fe/Board.h"
#include "fe/StateController.h"
#include "fe/GameConstants.h"

namespace fe
{

class FGame
{
private:
	Board* 	  			m_Board;
	TPlayerID 			m_CurrentPlayer;
	UI16	  			m_Wins[2];
	StateController 	m_State;
	sf::RenderWindow	m_Window;

	void MainLoop();
	void HandleInput();
	bool CheckWin() const;
	void Draw(sf::RenderWindow& window) const;
	void Reset();

public:
	FGame(const UI16 windowWidth = 500, const UI16 windowHeight = 500);
	FGame(const FGame& toCopy);
	FGame& operator=(const FGame& toCopy);
	~FGame();

	void Run();
};

}

#endif
