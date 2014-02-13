#include <iostream>
#include "fe/FGame.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
FGame::FGame(const UI16 windowWidth, const UI16 windowHeight) :
	m_Board(nullptr),
	m_CurrentPlayer(TPlayerID::PLAYER1),
	m_Score{ 0, 0 },
	m_HUD(Vector2f(windowWidth, windowWidth * 0.08)),
	m_Window(VideoMode(windowWidth, windowHeight), "Tic-Tac-Toe")
{
	m_InternalState.SetRunCallback(bind(&FGame::MainLoop, this));
	
	m_Board = new Board(GameConstants::BoardSize,   GameConstants::SquareSize,
						Vector2i(windowWidth * 0.5, windowHeight * 0.5),
						GameConstants::SquareTexture);

	m_Board->SetPlayerChip(TPlayerID::PLAYER1, Sprite(GameConstants::Player1Texture));
	m_Board->SetPlayerChip(TPlayerID::PLAYER2, Sprite(GameConstants::Player2Texture));
}

FGame::~FGame()
{
	if (m_Board != nullptr)
		delete m_Board;
	
	m_Board = nullptr;
}

// =============================================================================
//	PRIVATE AND PROTECTED METHODS
// =============================================================================
void FGame::MainLoop()
{
	while (m_Window.isOpen())
    {
        Event event;
        while (m_Window.pollEvent(event))
        {
            HandleInput(event);
        }

        m_HUD.Update();

        m_Window.clear(Color::White);
        m_HUD.Draw(m_Window);
        m_Board->Draw(m_Window);
        m_Window.display();
    }
}

void FGame::HandleInput(const Event& event)
{
	if (m_InternalState.IsPaused() || m_InternalState.IsStopped())
		return;

	if (event.type == Event::Closed)
    	m_Window.close();

    if (event.type == Event::MouseButtonPressed)
    {
    	if (event.mouseButton.button == Mouse::Left)
        {
        	Vector2u bCoords;
            if (Window2BoardCoords(Vector2i(event.mouseButton.x, event.mouseButton.y),
            	bCoords, *m_Board) && m_Board->GetMovements()[bCoords.x][bCoords.y] == TPlayerID::NONE)
            {
            	m_Board->PutChip(bCoords.x, bCoords.y, m_CurrentPlayer);
            	
            	if (CheckWin())
            	{
            		if (m_CurrentPlayer == TPlayerID::PLAYER1)
            			++m_Score[0];
            		else
            			++m_Score[1];

            		m_HUD.UpdateScoreboard(m_Score);

            		if (m_CurrentPlayer == TPlayerID::PLAYER1)
            			m_HUD.UpdateGameMessage("Player 1 wins!");
            		else
            			m_HUD.UpdateGameMessage("Player 2 wins!");
            	}

            	if (CheckTie())
            	{
            		m_HUD.UpdateGameMessage("Tie!");
            	}
           		
           		NextPlayerTurn();
            }
            else
            {
            	string prevMessage = m_HUD.GetGameMessage();
            	m_HUD.UpdateGameMessage("Invalid movement",
            							1000,
            							[&, prevMessage] () { m_HUD.UpdateGameMessage(prevMessage); });
            }
        }
    }
}

void FGame::NextPlayerTurn()
{
	if (m_CurrentPlayer == TPlayerID::PLAYER1)
    	m_CurrentPlayer = TPlayerID::PLAYER2;
    else
    	m_CurrentPlayer = TPlayerID::PLAYER1;
}

bool FGame::CheckWin() const
{
	TPlayerMovements movements = m_Board->GetMovements();

	for (UI32 i = 0; i < m_Board->GetSize().x; ++i)
		if (CheckWinRow(i, movements))
			return true;

	for (UI32 i = 0; i < m_Board->GetSize().y; ++i)
		if (CheckWinColumn(i, movements))
			return true;

	if (CheckWinDiagonal(true, movements))
		return true;

	if (CheckWinDiagonal(false, movements))
		return true;

	return false;
}

bool FGame::CheckWinRow(const UI32 row, const TPlayerMovements& movements) const
{
	for (auto& movement : movements[row])
		if (movement != m_CurrentPlayer)
			return false;
	
	return true;
}

bool FGame::CheckWinColumn(const UI32 column, const TPlayerMovements& movements) const
{
	for (auto& row : movements)
		if (row[column] != m_CurrentPlayer)
			return false;

	return true;
}

bool FGame::CheckTie() const
{
	for (auto& row : m_Board->GetMovements())
		for (auto& movement : row)
			if (movement == TPlayerID::NONE)
				return false;

	return true;
}

bool FGame::CheckWinDiagonal(const bool leftRight, const TPlayerMovements& movements) const
{
	// The board must be squared
	if (m_Board->GetSize().x != m_Board->GetSize().y)
		return false;

	if (leftRight)
	{
		for (UI32 i = 0; i < m_Board->GetSize().x; ++i)
			if (movements[i][i] != m_CurrentPlayer)
				return false;

		return true;
	}

	for (UI32 i = 0; i < m_Board->GetSize().x; ++i)
		if (movements[i][m_Board->GetSize().x - 1 - i] != m_CurrentPlayer)
			return false;

	return true;
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void FGame::Run()
{
	m_InternalState.Run();
}

}
