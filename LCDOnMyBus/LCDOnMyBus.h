/*
 * IncFile1.h
 *
 * Created: 2014-12-20 12:38:36
 *  Author: michal
 */ 




#include "MyBus/MyBus.h"
#include "HD44780/HD44780.h"
#include "BigFont/BigFont.h"

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//=================================================================================================================================
#define MY_ADDRESS 21
#define MASTER_ADDRESS 1

// COMMANDS :

// Led
#define CMD_ENABLE_LED0								1		// No data
#define CMD_DISABLE_LED0							2		// No data
#define CMD_TOGGLE_LED0								3		// No data


// Port
#define CMD_GET_PORTB								10		// Byte
#define CMD_SET_PORTB								11		// Byte

// LCD
#define CMD_LCD_WRITE_CHARACTERS					20		// Characters
#define CMD_LCD_CLEAR								21		// No data
#define CMD_LCD_HOME								22		// No data
#define CMD_LCD_GoTo								23		// x, y
#define CMD_LCD_WRITE_CHARACTERS_HOME_LINE_WRAPE	24		// Characters, start at home


// Other
#define CMD_HELLO_WORLD								200		// Hello word










//#define MSG_CRC 
//=================================================================================================================================