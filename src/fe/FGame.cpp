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
            if (event.type == Event::Closed)
                m_Window.close();
            if (event.type == Event::MouseButtonPressed)
            {
            	if (event.mouseButton.button == Mouse::Left)
            	{
            		Vector2u bCoords;
            		if (Window2BoardCoords(Vector2i(event.mouseButton.x, event.mouseButton.y),
            			bCoords, *m_Board))
            		{
            			m_Board->PutChip(bCoords.x,
            						 	 bCoords.y,
            						 	 m_CurrentPlayer);
            			if (m_CurrentPlayer == TPlayerID::PLAYER1)
            				m_CurrentPlayer = TPlayerID::PLAYER2;
            			else
            				m_CurrentPlayer = TPlayerID::PLAYER1;
            		}
            	}
            }
        }

        m_Window.clear(Color::White);
        m_Board->Draw(m_Window);
        m_Window.display();
    }
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
void FGame::Run()
{
	m_State.Run();
}

}
