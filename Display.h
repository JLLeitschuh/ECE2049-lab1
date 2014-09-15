#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "Game.h"
#include <msp430.h>
#include <stdint.h>
#include "inc\hw_memmap.h"
#include "driverlibHeaders.h"
#include "CTS_Layer.h"

#include "peripherals.h"

#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"

#define MAX_X 102
#define MAX_Y 64

#define POSITION_MULTIPLIER_X  ((MAX_X) / (gameFieldSizeX + 1))
#define POSITION_MULTIPLIER_Y  ((MAX_Y) / (gameFieldSizeY + 1))

void displayAliens();


#endif //_Display_H_
