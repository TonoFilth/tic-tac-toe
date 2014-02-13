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
	m_Wins{ 0, 0 },
	m_Window(VideoMode(windowWidth, windowHeight), "Tic-Tac-Toe")
{
	GameConstants::Init();
	m_State.SetRunCallback(bind(&FGame::MainLoop, this));
	
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

        //if (CheckWin())
        //	cout << "Win" << endl;

        if (CheckTie())
        	cout << "Tie!" << endl;

        m_Window.clear(Color::White);
        m_Board->Draw(m_Window);
        m_Window.display();
    }
}

void FGame::HandleInput(const Event& event)
{
	if (m_State.IsPaused() || m_State.IsStopped())
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
            		cout << "Win" << endl;
           		
           		if (m_CurrentPlayer == TPlayerID::PLAYER1)
            		m_CurrentPlayer = TPlayerID::PLAYER2;
            	else
            		m_CurrentPlayer = TPlayerID::PLAYER1;
            }
            else
            {
            	cerr << "Invalid movement" << endl;
            }
        }
    }
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

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void FGame::Run()
{
	m_State.Run();
}

}
