#include "Game.h"
#include "Error.h"
#include <stdlib.h>
#include <stdio.h>

void generateNewGameField(int count){
	while(count != 0){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			int y;
			for(y = gameFieldSizeY-1; 0 < y; y--){
				if(gameField[x][y] == 0){
					gameField[x][y]= rand() % 2;
					if(gameField[x][y] == 1){
						count --;
					}
					if(count == 0){
						break;
					}
				}
			}
			if(count == 0){
				break;
			}
		}
	}
}


int performAlienMovement(){
	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			if ( gameField[x][y] == 1){
				gameField[x][y] = 0;
				if(y-1 < 0){
					//Game is over because aliens have reached the bottom.
					return 1;
				}
				gameField[x][y-1] = 1;
			}
		}
	}
	return 0;
}

int _isLevelWon(){
	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			if ( gameField[x][y] == 1){
				// There is at least one alien remaining.
				return 0;
			}
		}
	}
	return 1;
}

int killColumn(uint16_t column){
	assert (column >= 0);
	assert (column < gameFieldSizeX);

	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		if(gameField[column][y] == 1){
			gameField[column][y] = 0;
			break;
		}
	}
	return _isLevelWon();
}




void printGameField(){
	int y;
	for(y = gameFieldSizeY-1; 0 <= y; y--){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			printf(" %d ", gameField[x][y]);
		}
		printf("\n");
	}
}



