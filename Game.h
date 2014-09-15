#ifndef _GAME_H_
#define _GAME_H_

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define gameFieldSizeX 5
#define gameFieldSizeY 8


extern int gameField[gameFieldSizeX][gameFieldSizeY];

void generateNewGameField(int count);
int performAlienMovement();
int killColumn(uint16_t column);

#endif // _GAME_H_
