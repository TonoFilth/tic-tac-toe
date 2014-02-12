#include <iostream>
#include <SFML/Graphics.hpp>
#include "fe/FGame.h"

using namespace std;
using namespace sf;
using namespace fe;

int main(int argc, char** argv)
{
    //RenderWindow window(sf::VideoMode(500, 500), "TicTacToe");
    //Board board(Vector2u(3, 3), Vector2u(64, 64), Vector2i(250, 250), squareTexture);

    FGame game(GameConstants::WindowSize.x, GameConstants::WindowSize.y);
    game.Run();

    return 0;
}