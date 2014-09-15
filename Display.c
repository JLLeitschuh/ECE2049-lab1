#include "Display.h"

/**
 * Displays the Aliens on the LCD screen.
 */
void displayAliens(){
	GrClearDisplay(&g_sContext);
	//Iterate over the gameField
	GrStringDrawCentered(&g_sContext, "O", AUTO_STRING_LENGTH, MAX_X, MAX_Y, TRANSPARENT_TEXT);
	GrStringDrawCentered(&g_sContext, "O", AUTO_STRING_LENGTH, 0, MAX_Y, TRANSPARENT_TEXT);
	GrStringDrawCentered(&g_sContext, "O", AUTO_STRING_LENGTH, MAX_X, 0, TRANSPARENT_TEXT);
	GrStringDrawCentered(&g_sContext, "O", AUTO_STRING_LENGTH, 0, 0, TRANSPARENT_TEXT);
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
