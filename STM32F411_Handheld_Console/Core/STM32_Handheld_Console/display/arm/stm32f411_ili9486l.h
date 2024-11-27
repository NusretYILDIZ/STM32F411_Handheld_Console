/*
	MIT License

	Copyright (c) 2024 Nusret YILDIZ

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef __stm32f411_ili9486l_h
#define __stm32f411_ili9486l_h

#include <stm32f4xx_hal.h>

#define SCREEN_WIDTH     480
#define SCREEN_HEIGHT    320

// ILI9486L Instructions
#define NOP         0x00    // No Operation
#define SWRESET     0x01    // Soft Reset
#define SLPIN       0x10    // Sleep In
#define SLPOUT      0x11    // Sleep Out
#define PTLON       0x12    // Partial Mode On
#define NORON       0x13    // Normal Mode On
#define INVOFF      0x20    // Display Inversion Off
#define INVON       0x21    // Display Inversion On
#define DISOFF      0x28    // Display Off
#define DISON       0x29    // Display On
#define CASET       0x2A    // Column Address Set
#define PASET       0x2B    // Page Address Set
#define RAMWR       0x2C    // Memory Write
#define PTLAR       0x30    // Partial Area
#define VSCRDEF     0x33    // Vertical Scrolling Defition
#define MADCTL      0x36    // Memory Access Control
#define VSCRSADD    0x37    // Vertical Scrolling Start Address
#define IDMOFF      0x38    // Idle Mode Off
#define IDMON       0x39    // Idle Mode On
#define COLMOD      0x3A    // Interface Pixel Format
#define RAMWRC      0x3C    // Memory Write Control
#define IFMODE      0xB0    // Interface Mode Control
#define FRMCTR1     0xB1    // Frame Rate Control (In Normal Mode/Full Colors)
#define FRMCTR2     0xB2    // Frame Rate Control (In Idle Mode/8 Colors)
#define FRMCTR3     0xB3    // Frame Rate Control (In Partial Mode/Full Colors)
#define INVTR       0xB4    // Display Inversion Control
#define ETMOD       0xB7    // Entry Mode Set
#define PWCTRL1     0xC0    // Power Control 1
#define PWCTRL2     0xC1    // Power Control 2
#define PWCTRL3     0xC2    // Power Control 3 (For Normal Mode)
#define PWCTRL4     0xC3    // Power Control 4 (For Idle Mode)
#define PWCTRL5     0xC4    // Power Control 5 (For Partial Mode)
#define VMCTRL      0xC5    // VCOM Control
#define PGAMCTRL    0xE0    // Positive Gamma Control
#define NGAMCTRL    0xE1    // Negative Gamma Control

// Output Pins
#define D11_LO    GPIOA->BSRR = GPIO_PIN_15 << 16
#define D11_HI    GPIOA->BSRR = GPIO_PIN_15

// GPIO Speed = Medium -> 6~10 ns
#define WR_LO     GPIOA->BSRR = GPIO_PIN_8 << 16
#define WR_HI     GPIOA->BSRR = GPIO_PIN_8

#define RS_CMD    GPIOA->BSRR = GPIO_PIN_9 << 16
#define RS_DAT    GPIOA->BSRR = GPIO_PIN_9

#define RST_LO    GPIOA->BSRR = GPIO_PIN_10 << 16
#define RST_HI    GPIOA->BSRR = GPIO_PIN_10

#define CS_LO     //GPIOA->BSRR = GPIO_PIN_14 << 16
#define CS_HI     //GPIOA->BSRR = GPIO_PIN_14

// Macros For Sending Data
#define tft_set_data_8(data_8)      GPIOB->BSRR = (0xFFFF0000 | (uint8_t)(data_8))

#define tft_set_data_16(data_16)    GPIOB->BSRR = (0xFFFF0000 | (uint16_t)(data_16))//; \
                                    //((uint16_t)(data_16) & (uint16_t)0x0800) ? (D11_HI) : (D11_LO)

//#define tft_write_pulse()        WR_LO; WR_LO; WR_LO; WR_LO; WR_LO;  WR_HI; WR_HI; WR_HI; WR_HI
#define tft_write_pulse()        WR_LO;   WR_HI
#define tft_write_8(data_8)      tft_set_data_8((data_8));   tft_write_pulse()
#define tft_write_16(data_16)    tft_set_data_16((data_16)); tft_write_pulse()

#define tft_start_write()    CS_LO
#define tft_end_write()      CS_HI

#define tft_send_command(cmd)    RS_CMD; tft_start_write(); tft_write_8((cmd)); RS_DAT; tft_end_write()
#define tft_send_data(dat)       tft_start_write(); tft_write_8((dat));  tft_end_write()
#define tft_send_color(col)      tft_start_write(); tft_write_16((col)); tft_end_write()

#define tft_set_write_window(x0, y0, x1, y1)    RS_CMD; tft_write_8(CASET); RS_DAT; \
                                                tft_write_8((x0) >> 8); tft_write_8(x0); \
                                                tft_write_8((x1) >> 8); tft_write_8(x1); \
                                                RS_CMD; tft_write_8(PASET); RS_DAT; \
                                                tft_write_8((y0) >> 8); tft_write_8(y0); \
                                                tft_write_8((y1) >> 8); tft_write_8(y1); \
                                                RS_CMD; tft_write_8(RAMWR); RS_DAT

/*void tft_set_write_window(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	RS_CMD; tft_write_8(CASET); RS_DAT;
	tft_write_8(((x) >> 8)); tft_write_8((x));
	tft_write_8(((x + w - 1) >> 8)); tft_write_8((x + w - 1));
	RS_CMD; tft_write_8(PASET); RS_DAT;
	tft_write_8(((y) >> 8)); tft_write_8((y));
	tft_write_8(((y + h - 1) >> 8)); tft_write_8((y + h - 1));
	RS_CMD; tft_write_8(RAMWR); RS_DAT;
}*/

#define tft_send_pulses(count)      uint32_t tft_pixels_left = (uint32_t)(count); \
                                    do { \
                                        while(tft_pixels_left > 31) { \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_pixels_left -= 32; \
                                        } \
                                        while(tft_pixels_left > 7) { \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse(); \
                                            tft_pixels_left -= 8; \
                                        } \
                                        while(tft_pixels_left) { \
                                            tft_write_pulse(); \
                                            --tft_pixels_left; \
                                        } \
                                    } while(0)

/*void tft_send_pulses(uint32_t count)
{
	while(count > 31)
	{
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		count -= 32;
	}
	while(count > 7)
	{
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		tft_write_pulse();  tft_write_pulse();  tft_write_pulse();  tft_write_pulse();
		count -= 8;
	}
	while(count)
	{
		tft_write_pulse();
		--count;
	}
}*/

void init_ili9486l()
{
    // Clear all pins
    GPIOB->BSRR = 0xFFFF0000;
    
    // Set Control Pins High
    CS_HI;
    WR_HI;
    RS_DAT;
    RST_HI;
    
    // Hardware Reset
    RST_HI; HAL_Delay(5);
    RST_LO; HAL_Delay(20);
    RST_HI; HAL_Delay(150);
    
    // Initialise Display
    tft_send_command(SWRESET);    HAL_Delay(120);
    tft_send_command(SLPOUT);     HAL_Delay(120);
    
    // Select 16-bit Color
    tft_send_command(COLMOD);
    tft_send_data(0x55);
    
    // Step-up Cycle For Step-up Circuit 1/4/5 = 2 H
    // Step-up Cycle For Step-up Circuit 2/3   = 8 H
    tft_send_command(PWCTRL3);
    tft_send_data(0x44);
    
    // (whatever are these)
    tft_send_command(VMCTRL);
    tft_send_data(0x00);
    tft_send_data(0x00);
    tft_send_data(0x00);
    tft_send_data(0x00);
    
    tft_send_command(PGAMCTRL);
    tft_send_data(0x0F);
    tft_send_data(0x1F);
    tft_send_data(0x1C);
    tft_send_data(0x0C);
    tft_send_data(0x0F);
    tft_send_data(0x08);
    tft_send_data(0x48);
    tft_send_data(0x98);
    tft_send_data(0x37);
    tft_send_data(0x0A);
    tft_send_data(0x13);
    tft_send_data(0x04);
    tft_send_data(0x11);
    tft_send_data(0x0D);
    tft_send_data(0x00);
    
    tft_send_command(NGAMCTRL);
    tft_send_data(0x0F);
    tft_send_data(0x32);
    tft_send_data(0x2E);
    tft_send_data(0x0B);
    tft_send_data(0x0D);
    tft_send_data(0x05);
    tft_send_data(0x47);
    tft_send_data(0x75);
    tft_send_data(0x37);
    tft_send_data(0x06);
    tft_send_data(0x10);
    tft_send_data(0x03);
    tft_send_data(0x24);
    tft_send_data(0x20);
    tft_send_data(0x00);
    
    // Color Inversion Off
    tft_send_command(INVOFF);
    
    // Memory Access Control
    tft_send_command(MADCTL);
    tft_send_data(0xE8);
	
	// Frame Rate: 30 Hz, Div Ratio: 1, Clock Per Line: 17 clocks
	/*tft_send_command(FRMCTR1);
	tft_send_data(0x10);
	tft_send_data(0x11);*/
    
    // Display On
    tft_send_command(DISON);
}

#endif //__stm32f411_ili9486l_h
