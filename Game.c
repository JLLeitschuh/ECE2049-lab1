#include "Game.h"

 int gameField[gameFieldSizeX][gameFieldSizeY];

/**
 * Generates a game field using random values.
 * Allows you to generate the field with a given number of aliens
 * @param count The number of ailiens to generate on the field.
 */
void generateNewGameField(int count){
	//Initalize the array to all zeros.
	int x;
	for(x = 0; x < gameFieldSizeX; x ++){
		int y;
		for(y = 0; y < gameFieldSizeY; y++){
			gameField[x][y] = 0;
		}
	}

	//Now set the values of the array.
	while(count != 0){
		int y;
		for(y = gameFieldSizeY-1; 0 < y; y--){
			int x;
			for(x = 0; x < gameFieldSizeX; x++){
				if(gameField[x][y] == 0){
					gameField[x][y] = rand() % 2;
					if(gameField[x][y] != 0){
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

/**
 * Moves the aliens down by one position.
 * @return 1 if the game is over because the aliens have won.
 */
int performAlienMovement(){
	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			if ( gameField[x][y] != 0){
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

/**
 * Checks to see if the game has been won by the user
 * @returns 1 when the game is won by the user
 */
int _isLevelWon(){
	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		int x;
		for(x = 0; x < gameFieldSizeX; x++){
			if ( gameField[x][y] != 0){
				// There is at least one alien remaining.
				return 0;
			}
		}
	}
	return 1;
}

/**
 * Kills the lowest alien in a given column.
 * @param column the column to kill
 * @return 1 when the game is won by the user.
 */
int killColumn(uint16_t column){
	assert (column < gameFieldSizeX);

	int y;
	for(y = 0; y < gameFieldSizeY; y++){
		if(gameField[column][y] != 0){
			gameField[column][y] = 0;
			break;
		}
	}
	return _isLevelWon();
}


/*
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
*/
