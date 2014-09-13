#ifndef _GAME_H_
#define _GAME_H_

#include <assert.h>
#include <stdint.h>

#define gameFieldSizeX 5
#define gameFieldSizeY 4
int gameField[gameFieldSizeX][gameFieldSizeY];

void generateNewGameField(int count);
int performAlienMovement();
void printGameField();
int killColumn(uint16_t column);



#endif // _GAME_H_