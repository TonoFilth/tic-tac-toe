#ifndef __FGAME_H__
#define __FGAME_H__

namespace fe
{

class FGame
{
public:
	FGame();
	FGame(const FGame& toCopy);
	FGame& operator=(const FGame& toCopy);
	~FGame();
};

}

#endif
