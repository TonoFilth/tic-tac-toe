#include "fe/GameConstants.h"

using namespace std;
using namespace sf;

namespace fe
{

// =============================================================================
//	CONSTANTS
// =============================================================================
const string GameConstants::Player1TextureFile = "assets/images/chip-a.png";
const string GameConstants::Player2TextureFile = "assets/images/chip-b.png";
const string GameConstants::SquareTextureFile  = "assets/images/square.png";
const string GameConstants::HudFontFile		   = "assets/fonts/Monaco.ttf";

const Vector2u GameConstants::WindowSize(500, 500);
const Vector2u GameConstants::BoardSize(3, 3);
const Vector2u GameConstants::SquareSize(64, 64);

const Color GameConstants::HudBackgroundColor(0, 0, 0, 200);
const Color GameConstants::HudPlayerNameColor(255, 255, 255, 255);
const Color GameConstants::HudScoreboardColor(255, 255, 255, 255);
const Color GameConstants::HudGameMessageColor(0, 0, 0, 255);

const UI32 GameConstants::HudPlayerNameTextSize  = 24;
const UI32 GameConstants::HudScoreboardTextSize  = 24;
const UI32 GameConstants::HudGameMessageTextSize = 30;

// =============================================================================
//	STATIC FIELDS
// =============================================================================
Texture GameConstants::Player1Texture;
Texture GameConstants::Player2Texture;
Texture GameConstants::SquareTexture;

Font GameConstants::HudFont;

bool GameConstants::st_Initialized = false;

// =============================================================================
//	STATIC METHODS
// =============================================================================
bool GameConstants::Init()
{
	if (st_Initialized)
		return false;

	if (!Player1Texture.loadFromFile(Player1TextureFile) ||
		!Player2Texture.loadFromFile(Player2TextureFile) ||
		!SquareTexture.loadFromFile(SquareTextureFile))
	{
		cerr << "Can't load textures" << endl;
		return false;
	}

	if (!HudFont.loadFromFile(HudFontFile))
	{
		cerr << "Can't load font file: " << HudFontFile << endl;
		return false;
	}

	st_Initialized = true;

	return true;
}

}
