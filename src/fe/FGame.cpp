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
	m_CurrentPlayer(TPlayerID::PLAYER2),
	m_CurrentPlayerSprite(GameConstants::Player1Texture),
	m_Score{ 0, 0 },
	m_GameState(TGameState::PLAYING),
	m_HUD(Vector2f(windowWidth, windowWidth * 0.08)),
	m_Window(VideoMode(windowWidth, windowHeight), "Tic-Tac-Toe")
{
	m_Window.setMouseCursorVisible(false);

	m_InternalState.SetRunCallback(bind(&FGame::MainLoop, this));
	m_InternalState.SetStopCallback(bind(&FGame::OnRoundEnd, this));
	
	m_Board = new Board(GameConstants::BoardSize,   GameConstants::SquareSize,
						Vector2i(windowWidth * 0.5, windowHeight * 0.5),
						GameConstants::SquareTexture);

	m_Board->SetPlayerChip(TPlayerID::PLAYER1, Sprite(GameConstants::Player1Texture));
	m_Board->SetPlayerChip(TPlayerID::PLAYER2, Sprite(GameConstants::Player2Texture));
	NextPlayerTurn();
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
        m_CurrentPlayerSprite.setPosition(
        	Mouse::getPosition(m_Window).x, Mouse::getPosition(m_Window).y);

        m_Window.clear(Color::White);
        m_Board->Draw(m_Window);
        m_HUD.Draw(m_Window);
        m_Window.draw(m_CurrentPlayerSprite);
        m_Window.display();
    }
}

void FGame::HandleInput(const Event& event)
{
	if (event.type == Event::Closed)
    	m_Window.close();

    if (m_InternalState.IsPaused())
		return;

	if (m_InternalState.IsStopped())
	{
		if (event.type == Event::MouseButtonPressed)
			NextRound();

		return;
	}

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
            		m_GameState = TGameState::WON;
            		m_InternalState.Stop();
            		return;
            	}

            	if (CheckTie())
            	{
            		m_GameState = TGameState::TIE;
            		m_InternalState.Stop();
            		return;
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
    {
    	m_CurrentPlayer = TPlayerID::PLAYER2;
    	m_CurrentPlayerSprite.setTexture(GameConstants::Player2Texture);
    	m_HUD.UpdateGameMessage("Player's 2 turn");
    }
    else
    {
    	m_CurrentPlayer = TPlayerID::PLAYER1;
    	m_CurrentPlayerSprite.setTexture(GameConstants::Player1Texture);
    	m_HUD.UpdateGameMessage("Player's 1 turn");
    }
}

void FGame::NextRound()
{
	m_GameState = TGameState::PLAYING;
	m_Board->Reset();
	NextPlayerTurn();
	m_InternalState.Run();
}

void FGame::OnRoundEnd()
{
	if (m_GameState == TGameState::WON)
	{
		if (m_CurrentPlayer == TPlayerID::PLAYER1)
		{
			++m_Score[0];
			m_HUD.UpdateGameMessage("Player 1 wins!");
		}
		else
		{
			++m_Score[1];
			m_HUD.UpdateGameMessage("Player 2 wins!");
		}

		m_HUD.UpdateScoreboard(m_Score);
	}

	if (m_GameState == TGameState::TIE)
		m_HUD.UpdateGameMessage("Tie!");
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
