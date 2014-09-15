#include "Display.h"

/**
 * Displays the Aliens on the LCD screen.
 */
void displayAliens(){
	GrClearDisplay(&g_sContext);
	//Iterate over the gameField
	int x;
	for(x = 0; x < gameFieldSizeX; x++){
		int y;
		for(y = 0; y < gameFieldSizeY; y++){
			if(gameField[x][y] != 0){
				//Print the given element on the 
				GrStringDrawCentered(&g_sContext, "X", AUTO_STRING_LENGTH, (x+1) * POSITION_MULTIPLIER_X, (gameFieldSizeY - y + 1) * POSITION_MULTIPLIER_Y, TRANSPARENT_TEXT);
			}
		}
	}
	GrFlush(&g_sContext);
}
