/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : goldelox_core.h                                                  *
* Description : Header file for core routines for interfacing to              *
*               the Goldelox SGC serial display by 4D systems                 *
*                                                                             *
* This program is free software; you can redistribute it and/or               *
* modify it under the terms of the GNU General Public License                 *
* as published by the Free Software Foundation; version 2                     *
* of the License.                                                             *
                                                                              *
* This program is distributed in the hope that it will be useful,             *
* but WITHOUT ANY WARRANTY; without even the implied warranty of              *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
* GNU General Public License for more details.                                *
*                                                                             *
* As a special exception, if other files instantiate templates or             *
* use macros or inline functions from this file, or you compile this          *
* file and link it with other works to produce a work based on this file,     *
* this file does not by itself cause the resulting work to be covered         *
* by the GNU General Public License. However the source code for this         *
* file must still be made available in accordance with section (3) of         *
* the GNU General Public License.                                             *
*                                                                             *
* This exception does not invalidate any other reasons why a work based       *
* on this file might be covered by the GNU General Public License.            *
*                                                                             *
*                                         (c)2015 Pratik Panda                *
*							Website: www.PratikPanda.com        *
*							support@PratikPanda.com             *  
\*****************************************************************************/

#ifndef _goldelox_core_H_
#define _goldelox_core_H_

#define 	rgb(x,y,z)		z|(y<<5)|(x<<11)		//converts RGB values to unsigned short
									// maximum values rgb (31, 63, 31)
#define	msb16(x)		(x>>8)
#define	lsb16(x)		(x & 0x00FF)

#define 	gfx_SOLID		0x00
#define	gfx_OUTLINE		0x01

#define 	ACK			0x06

#define 	gfx_SMALL		0x00		//7x5
#define	gfx_MEDIUM		0x01
#define 	gfx_LARGE		0x02

#define 	gfx_TRANSPARENT	0x00
#define	gfx_OPAQUE		0x01

#define	gfx_cos(phi)	sin[(90 - phi)/3]
#define	gfx_sin(phi)	sin[phi/3]

void gfx_primitive (void);		//For debugging
void gfx_sendcmd(char i);
void gfx_info(void);
void gfx_boot (void);
void gfx_autobaud(void);
void gfx_replacebackcolor(unsigned short color);
void gfx_clearscreen (void);
void gfx_displayoff (void);
void gfx_displayon (void);
void gfx_setcontrast (unsigned char level);			//Contrast in 0-15 levels
void gfx_sleep (void);
void gfx_sound (unsigned short frequency, unsigned short duration);	//Frequency in Hz, duration in ms
void gfx_circle (unsigned char x, unsigned char y, unsigned char radius, unsigned short color);
void gfx_disc (unsigned char x, unsigned char y, unsigned char radius, unsigned short color);
void gfx_triangle (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char x3, unsigned char y3, unsigned short color);
void gfx_drawbitmap (unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned short *color);
void gfx_setbackcolor (unsigned short color);
void gfx_line (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned short color);
void gfx_putpixel (unsigned char x, unsigned char y, unsigned short color);
void gfx_rectangle (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned short color, unsigned char type);
void gfx_fontsize (unsigned char font);
void gfx_textmode (unsigned char blend);
void gfx_formattedtext (unsigned char row, unsigned char col, unsigned char font, unsigned short color, unsigned char *txt);

void gfx_sd_init (void);
void gfx_sd_bmp (unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned short addrH, unsigned short addrL);
void gfx_sd_object (unsigned int addr);
void gfx_sd_setaddr (unsigned int addr);
void gfx_sd_bmp_test (unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned char b1, unsigned char b2, unsigned char b3);

void gfx_radial_line (unsigned char base_x, unsigned char base_y, unsigned char r1, unsigned short phi1, unsigned char r2, unsigned short phi2, unsigned short color);
void gfx_radial_circle (unsigned char base_x, unsigned char base_y, unsigned char r1, unsigned short phi1, unsigned char radius, unsigned short color);

#endif
