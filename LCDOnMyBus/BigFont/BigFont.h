/*
 * BigFont.h
 *
 * Created: 2014-12-31 23:08:16
 *  Author: michal
 */ 


#ifndef BIGFONT_H_
#define BIGFONT_H_

#include "../HD44780/HD44780.h"

#include <avr/pgmspace.h>



#define LCD_WIDTH		16
#define LCD_HEIGHT		2

void display_number(uint8_t c, uint8_t x, uint8_t y);
void display_number_x(uint8_t c, uint8_t x);
void load_big_font(void);



#endif /* BIGFONT_H_ */