/*
 * This program will be used to create the space invader game
 * It uses the code given in the demo5529.c file as a base
 * Written by: Susan Jarvis
 * Edited by:  Daniel Benson
 * djbenson@wpi.edu
 * Lab 1 ECE 2049
 */

#include <msp430.h>
#include <stdint.h>
#include "inc\hw_memmap.h"
#include "driverlibHeaders.h"
#include "CTS_Layer.h"

#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and cap touch buttons are implemented. It is useful
 * to organize your code by putting like functions together in
 * files. You include the header associated with that file(s)
 * into the main file of your project.
 */
#include "peripherals.h"
#include "Display.h"
#include "Game.h"


#define BUTTON_X   BIT0
#define BUTTON_SQU BIT1
#define BUTTON_OCT BIT2
#define BUTTON_TRI BIT3
#define BUTTON_CIR BIT4

 // define the alien struct
struct alien{
	int x;
	int y;
	//char shape[1];
};

// Define global variables
long stringWidth = 0;
struct alien aliens[10];

typedef enum{
	WELCOME,
	COUNTDOWN,
	CHECK_CAP_PADS,
	MOVE_ALIENS,
	LEVEL_WON,
	GAME_OVER
} GameState;

// Function prototypes for this file
void swDelay(char numLoops);
void generateNewGameField(int count);

int getRowFromButton(int buttonIn){
	switch(buttonIn){
	case BUTTON_X: return 0;
	case BUTTON_SQU: return 1;
	case BUTTON_OCT: return 2;
	case BUTTON_TRI: return 3;
	case BUTTON_CIR: return 4;
	default: return -1;
	}
}



// Main Function
void main(void){

	// Variables
	GameState state = WELCOME;
	int level = 0;
	//Keeps track of the number of times we have attempted to move the aliens.
	uint16_t moveAlienCount = 1;

	int numAliens, counter;
	long long int i = 0;
	int gameStarted = 0;

	// Variable to record button state for later
	CAP_BUTTON keypressed_state;

	// Stop WDT
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	//Perform initializations (see peripherals.c)
	configTouchPadLEDs();
	configDisplay();
	configCapButtons();

	/* Monitor Capacitive Touch Pads in endless "forever" loop */
	while(1){
		P1OUT |= (LED4+LED5+LED6+LED7+LED8);   // turn on all 5 LEDs

		// Check cap touch keys
		keypressed_state = CapButtonRead();

		// if a key was preseed turn off its LED and set the state
		if (keypressed_state) {
			P1OUT &= ~(keypressed_state << 1);
		}

		//Run a switch statement that controls the flow of the game
		switch (state) {
		case WELCOME: // Display the welcome screen
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "Space Invaders!!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrStringDrawCentered(&g_sContext, "Press X to Start!", AUTO_STRING_LENGTH, 51, 32, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);

			// if the X Pad is pressed the state should be set to start the countdown and then draw the aliens
			if (keypressed_state == BUTTON_X){
				state = COUNTDOWN;
			}
			break;

		case COUNTDOWN: // Countdown and generate the aliens
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "3!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(1);
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "2!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(1);
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "1!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(1);
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "BEGIN!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(1);
			GrClearDisplay(&g_sContext);

			// Fill an array of the alien with random variables
			// May need to check that the same spot is not being filled more than once with an array of some sort
			if (level == 0){
				counter = 3;
			}
			if (level == 1){
				counter = 5;
			}
			if (level == 2){
				counter = 10;
			}
			generateNewGameField(counter);
			displayAliens();

			state = CHECK_CAP_PADS;
			break;

		case CHECK_CAP_PADS: // Check the Capacitive pads

			// Check cap touch keys
			keypressed_state = CapButtonRead();
			// if a buttons is pushed shoot the "alien" in that spot (Remove it from the screen)

			int rowKilled = getRowFromButton(keypressed_state);
			if(rowKilled != -1){
				uint16_t levelWon = killColumn(rowKilled);
				displayAliens();
				if(levelWon == 1){
					//Level has been won
					state = LEVEL_WON;
					break;
				}
			}

			state = MOVE_ALIENS;

			// check the position of the  button pushed and remove the alien in the array with the lowest
			// y value with the given x value. Then loop to rewrite the array to the screen
			//subtract from the number of aliens
			//counter = numAliens-1;
			//numAliens--;
			break;
		case MOVE_ALIENS: // Move Aliens
			if(moveAlienCount % (50 / (1 + level)) == 0){ //The + 1 is to prevent a devide by zero error
				int gameOver = performAlienMovement();
				displayAliens();
				if(gameOver == 1){
					state = GAME_OVER;
					break;
				}
			}
			state = CHECK_CAP_PADS;

			moveAlienCount ++;
			break;
		case LEVEL_WON:
			//Display move on
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "LEVEL UP!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(1);

			level ++;
			state = COUNTDOWN;
			break;
		case GAME_OVER:
			//Display Game Over!
			GrClearDisplay(&g_sContext);
			GrStringDrawCentered(&g_sContext, "THE ALIENS KILLED", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
			GrStringDrawCentered(&g_sContext, "THE ENTIRE HUMAN", AUTO_STRING_LENGTH, 51, 32, TRANSPARENT_TEXT);
			GrStringDrawCentered(&g_sContext, "RACE", AUTO_STRING_LENGTH, 51, 48, TRANSPARENT_TEXT);
			GrFlush(&g_sContext);
			swDelay(3);

			level = 0;
			state = WELCOME;
			break;
		}

		/*
		// move the aliens down the screen
		// level zero speed
		if (i == 50 && gameStarted == 1){
			// move one of the aliens in the array down one then print the array again
			counter = numAliens;
			aliens[numAliens-1].y += 12;
			GrClearDisplay(&g_sContext);
			while (counter != 0){
				GrStringDrawCentered(&g_sContext, "X", AUTO_STRING_LENGTH, aliens[counter-1].x*20+4, aliens[counter-1].y, TRANSPARENT_TEXT);
				counter--;
			}
			GrFlush(&g_sContext);
			// reset i
			i = 0;
		}

		if (level == 1 && i == 25){
			// move one of the aliens in the array down one then print the array again
			counter = numAliens;
			aliens[numAliens-1].y += 12;
			GrClearDisplay(&g_sContext);
			while (counter != 0){
				GrStringDrawCentered(&g_sContext, "X", AUTO_STRING_LENGTH, aliens[counter-1].x*20+4, aliens[counter-1].y, TRANSPARENT_TEXT);
				counter--;
			}
			GrFlush(&g_sContext);
			// reset i
			i =0;
		}

		if (level == 2 && i == 15){
			// move one of the aliens in the array down one then print the array again
			counter = numAliens;
			aliens[numAliens-1].y += 12;
			GrClearDisplay(&g_sContext);
			while (counter != 0){
				GrStringDrawCentered(&g_sContext, "X", AUTO_STRING_LENGTH, aliens[counter-1].x*20+4, aliens[counter-1].y, TRANSPARENT_TEXT);
				counter--;
			}
			GrFlush(&g_sContext);
			// reset i
			i =0;
		}

		if(numAliens == 0 && gameStarted == 1){
			// end the game if level 2 or increase level
			if (level == 2){
				GrClearDisplay(&g_sContext);
				GrStringDrawCentered(&g_sContext, "Congrats you won!", AUTO_STRING_LENGTH, 51, 16, TRANSPARENT_TEXT);
				GrFlush(&g_sContext);
				break;
			}
			else{
				level++;
			}
		}

		i++;
		*/
	}
}


void swDelay(char numLoops){
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent optimization
										// by compiler

	for (j=0; j<numLoops; j++){
		i = 50000 ;					// SW Delay
		while (i > 0){				// could also have used while (i)
			i--;
		}
	}
}

/*
void generateNewGameField(int count){
	while(count != 0){
		for(int x = 0; x < gameFieldSizeX; x++){
			for(int y = gameFieldSizeY-1; 0 < y; y--){
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
}*/
