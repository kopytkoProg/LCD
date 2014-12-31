/*
* BlinkLedOnUsartDemand.c
*
* Created: 2014-12-19 15:30:15
*  Author: michal
*/
// F_CPU=8000000UL DEFINED IN COPILATION OPTIONS
#include "LCDOnMyBus.h"
#define DIODES_PORT (_BV(DDB0)|_BV(DDB1)|_BV(DDB6)|_BV(DDB7))
//--------------------------------------------------------------




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

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

void display_number_x(uint8_t c, uint8_t x)
{display_number(c,x,0);}
//
//void display_number_x(uint8_t c, uint8_t x)
//{display_number(c,x,0);}

void load_big_font(void)
{
	LCD_WriteCommand(HD44780_CGRAM_SET);
	for(int i = 0; i < 64; i++)
	{
		LCD_WriteData(pgm_read_byte_near(gBigFontShapeTable + i));
	}
}


//--------------------------------------------------------------
int main(void)
{
	

	DDRB |= DIODES_PORT;													// set out PB (for diodes)
	LCD_Initalize();
	
	load_big_font();
	
	LCD_Home();
	LCD_Clear();
	
	
	display_number_x(1, 0);
	display_number_x(2, 4);
	
	LCD_GoTo(7,0);
	LCD_WriteData(0xA1);
	LCD_GoTo(7,1);
	LCD_WriteData(0xA1);
	
	display_number_x(3, 8);
	display_number_x(4, 12);
	
	
	init_my_buss();
	
	
	sei();																	// Enables interrupts

	PORTB |= (_BV(PB0));
	
	while(1)
	{
		
		if (usart_rx_bufor_ind >= 4 && usart_rx_bufor[MSG_DATA_LENGTH] + 4 == usart_rx_bufor_ind)	// great or equal 4 because packet always have address, command,  length and CRC
		{																							//(End is when usart_rx_bufor_ind is equals 4(addr, cmd, length, crc) + usart_rx_bufor_ind[1](length of data field))
			
			if(usart_rx_bufor[usart_rx_bufor_ind-1] == crc(usart_rx_bufor, usart_rx_bufor_ind - 1)	// check CRC
			&& usart_rx_bufor[MSG_ADDRESS] == MY_ADDRESS)											// check Address
			{
				//char msg[] = {1, 2, 2, 'O', 'K', 0};
				usart_rx_bufor[0] = MASTER_ADDRESS;
				
				switch (usart_rx_bufor[MSG_COMMAND])
				{
					//--------------------------------------------------------------
					
					case CMD_ENABLE_LED0:
					PORTB |= (_BV(PB0));
					break;
					
					//--------------------------------------------------------------
					
					case CMD_DISABLE_LED0:
					PORTB &= ~(_BV(PB0));
					break;
					
					//--------------------------------------------------------------
					
					case CMD_TOGGLE_LED0:
					PORTB ^= (_BV(PB0));
					break;
					
					//--------------------------------------------------------------
					
					case CMD_SET_PORTB:
					PORTB = (PORTB & ~DIODES_PORT) | (DIODES_PORT & usart_rx_bufor[MSG_DATA_START]);
					break;
					
					//--------------------------------------------------------------
					
					case CMD_LCD_WRITE_CHARACTERS:
					
					for(int i = 0; i < usart_rx_bufor[MSG_DATA_LENGTH]; i++)
					{
						//if(i % LCD_WIDTH == 0) LCD_GoTo(0, i / LCD_WIDTH);
						LCD_WriteData(usart_rx_bufor[MSG_DATA_START + i]);
					}
					
					break;

					//--------------------------------------------------------------
					
					case CMD_LCD_CLEAR:
					LCD_Clear();
					break;
					
					//--------------------------------------------------------------
					
					case CMD_LCD_HOME:
					LCD_Home();
					break;
					//--------------------------------------------------------------
					
					case CMD_LCD_GoTo:
					LCD_GoTo(usart_rx_bufor[MSG_DATA_START], usart_rx_bufor[MSG_DATA_START+1]);
					break;
					
					//--------------------------------------------------------------
					
					case CMD_GET_PORTB:
					usart_rx_bufor[MSG_DATA_START] = PORTB & DIODES_PORT;
					usart_rx_bufor[MSG_DATA_LENGTH] = 1;
					usart_rx_bufor_ind += 1;								// add one because response contain 1 byte of data
					
					break;
					
					//--------------------------------------------------------------
					
					default:
					/* UNKNOWN */
					break;
				}
				usart_rx_bufor[usart_rx_bufor_ind - 1] = crc(usart_rx_bufor, usart_rx_bufor_ind - 1);
				send_data(usart_rx_bufor, usart_rx_bufor_ind);					// Send response
				usart_rx_bufor_ind = 0;

			}
			
		}
	}
}
//--------------------------------------------------------------
//--------------------------------------------------------------


