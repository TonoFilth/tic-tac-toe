#ifndef __FGAME_H__
#define __FGAME_H__

#include "fe/Board.h"
#include "fe/StateController.h"
#include "fe/GameConstants.h"
#include "fe/GameHud.h"

namespace fe
{

class FGame
{
private:
	Board* 	  		 m_Board;
	TPlayerID 		 m_CurrentPlayer;
	UI16	  		 m_Wins[2];
	StateController  m_InternalState;
	GameHud			 m_HUD;
	sf::RenderWindow m_Window;

	void MainLoop();
	void HandleInput(const sf::Event& event);
	void NextPlayerTurn();

	bool CheckWin() const;
	bool CheckWinRow(const UI32 row, const TPlayerMovements& movements) const;
	bool CheckWinColumn(const UI32 col, const TPlayerMovements& movements) const;
	bool CheckWinDiagonal(const bool leftRight, const TPlayerMovements& movements) const;
	bool CheckTie() const;

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
