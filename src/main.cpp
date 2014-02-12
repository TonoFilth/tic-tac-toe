#include <iostream>
#include <SFML/Graphics.hpp>
#include "fe/Board.h"

using namespace std;
using namespace sf;
using namespace fe;

int main(int argc, char** argv)
{
    Texture squareTexture;
    Texture chipATexture;
    if (!squareTexture.loadFromFile("assets/images/square.png") ||
        !chipATexture.loadFromFile("assets/images/chip-a.png"))
        cerr << "Error opening texture" << endl;

	RenderWindow window(sf::VideoMode(500, 500), "TicTacToe");
    Board board(Vector2u(3, 3), Vector2u(64, 64), Vector2i(250, 250), squareTexture);

    Sprite sprt(chipATexture);
    board.SetPlayerChip(TPlayerID::PLAYER1, sprt);

    board.PutChip(2, 2, TPlayerID::PLAYER1);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        board.Draw(window);
        window.display();
    }

    return 0;
}