#ifndef _Display_H_
#define _Display_H_
#include "Game.h"

#define MAX_X 102
#define MAX_Y 64

#define POSITION_MULTIPLIER_X ((MAX_X) / (gameFieldSizeX + 1))
#define POSITION_MULTIPLIER_Y ((MAX_Y) / (gameFieldSizeY + 1))

void displayAliens();


#endif //_Display_H_