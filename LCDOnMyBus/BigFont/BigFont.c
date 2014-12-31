/*
* BigFont.c
*
* Created: 2014-12-31 23:08:05
*  Author: michal
*/

#include "BigFont.h"

// ============== Big font shape table ==============
uint8_t const PROGMEM gBigFontShapeTable[] = {
	//*	LT[8, 0] =
	0b00111,
	0b01111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	//*	UB[8, 8] =
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	//*	RT[8, 16] =
	0b11100,
	0b11110,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	//*	LL[8, 24] =
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b01111,
	0b00111,
	//*	LB[8, 32] =
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	//*	LR[8, 40] =
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11110,
	0b11100,
	//*	UMB[8, 48] =
	0b11111,
	0b11111,
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	//*	LMB[8, 56] =
	0b11111,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111


};

// Numbers created using big font
uint8_t	const gBigFontAsciiTable[] PROGMEM = {
	0,	1,	2,	3,	4,	5,		//	0x30	0
	32,	1,	2,	32,	32,	5,		//	0x31	1
	6,	6,	2,	3,	7,	7,		//	0x32	2
	6,	6,	2,	7,	7,	5,		//	0x33	3
	3,	4,	2,	32,	32,	5,		//	0x34	4
	255,6,	6,	7,	7,	5,		//	0x35	5
	0,	6,	6,	3,	7,	5,		//	0x36	6
	1,	1,	2,	32,	0,	32,		//	0x37	7
	0,	6,	2,	3,	7,	5,		//	0x38	8
	0,	6,	2,	32,	32,	5,		//	0x39	9
};


void display_number(uint8_t c, uint8_t x, uint8_t y)
{
	LCD_GoTo(x,y);
	for (int i=0; i < 3; i++)
	{
		LCD_WriteData(pgm_read_byte_near(gBigFontAsciiTable + c * 6 + i));
	}

	LCD_GoTo(x,y+1);
	for (int i=3; i < 6; i++)
	{
		LCD_WriteData(pgm_read_byte_near(gBigFontAsciiTable  + c * 6 + i));
	}
	
}

void display_number_x(uint8_t c, uint8_t x)
{
	display_number(c,x,0);
}


void load_big_font(void)
{
	LCD_WriteCommand(HD44780_CGRAM_SET);
	for(int i = 0; i < 64; i++)
	{
		LCD_WriteData(pgm_read_byte_near(gBigFontShapeTable + i));
	}
}