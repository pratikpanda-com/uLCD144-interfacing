/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : goldelox_core.c                                                  *
* Description : This file contains all the core routines for interfacing to   *
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

#include "goldelox_core.h"
#include "goldelox_interface.h"
#include "../sys_core/CPU_activity.h"

extern struct text_property
{
	unsigned char text_size;
	unsigned char text_mode;
	unsigned short text_color;
}text_style;
	
extern struct lcd_status
{
	unsigned char last_cmd_status;
}lcd_status;
unsigned char gfx_cmdstring [15];
//struct text_property text_style;
//struct lcd_status lcd_status;

//sin and cos values for radial coordinate caculation. 90 deg/3 = 30 readings
//You can put 90 readings if you need more accurate radial lines

unsigned char sin [] = {0, 13, 26, 39, 52, 65, 77,	\
				90, 102, 114, 125, 136, 147,	\
				157, 167, 177, 186, 194, 202,	\
				210, 217, 223, 229, 234, 238,	\
				242, 245, 247, 249, 250, 250};

void gfx_primitive ()
{
	//Empty function, no real use of this.
	//You may use this function to test any
	//genric function that you create. Always
	//better not to mess with functions that
	//are proven good
}

void gfx_boot (void)
{
	#if (CPU_ACTIVITY == 1)					//This macro activates an LED to show that the processor
		init_CPU_busy_LED ();				//entered data transmission routine. Good for detecting
		CPU_busy;						//stuck loops when transmitting data
	#endif
	
	gfx_interface_init();
	
	//Uncomment following lines to initialize text type in case you plan to use text types
	//text_style.text_size = gfx_SMALL;
	//text_style.text_mode = TRANSPARENT;
	//text_style.text_color= 0x0000;
	
	gfx_autobaud ();
	
	#if (CPU_ACTIVITY == 1)					//Done. CPU is now considered idle
		CPU_idle;						//This simply means no UART transaction is going on right now
	#endif
	
}

void gfx_autobaud(void)						//You can use the code returned by gfx_getbyte() to check for error
{
	gfx_sendbyte (0x55);
	gfx_getbyte ();						//NOTE: 2 characters ACTUALLY received after autobaud
	gfx_getbyte();						//This has not been mentioned in Goldelox manual
}

void gfx_info()							//Function to get back display information
{
	gfx_sendbyte (0x56);
	gfx_sendbyte (0x01);
	
	gfx_getbyte();
	gfx_getbyte();
	gfx_getbyte();
	gfx_getbyte();
	gfx_getbyte();

}

//Replace a particular background color by another color
//The LCD does this noticeably slowly so avoid using this
void gfx_replacebackcolor(unsigned short color)		
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x42);
	gfx_sendbyte (color>>8);
	gfx_sendbyte (color);
		
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Function to clear the Goldelox LCD screen
void gfx_clearscreen (void)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x45);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

//Set display off
void gfx_displayoff (void)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x59);
	gfx_sendbyte (0x01);
	gfx_sendbyte (0x00);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Set display on
void gfx_displayon (void)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x59);
	gfx_sendbyte (0x01);
	gfx_sendbyte (0x01);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Get the display contrast levels in 0-15
void gfx_setcontrast (unsigned char level)			//Contrast in 0-15 levels
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x59);
	gfx_sendbyte (0x02);
	gfx_sendbyte (level & 0x0F);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Make LCD module sleep
void gfx_sleep (void)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x5A);
	gfx_sendbyte (0x01);
	gfx_sendbyte (0x00);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Play sound for a particular frequency and duration in ms
void gfx_sound (unsigned short frequency, unsigned short duration)	//Frequency in Hz, duration in ms
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x4E);
	gfx_sendbyte (frequency>>8);	//MSB
	gfx_sendbyte (frequency);	//LSB later, big endian
	gfx_sendbyte (duration>>8);
	gfx_sendbyte (duration);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a circle at x,y of radius r and color RGB-5-6-5 format
void gfx_circle (unsigned char x, unsigned char y, unsigned char radius, unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x70);
	gfx_sendbyte (0x01);			//Wire frame drawings
	
	gfx_getbyte ();
	
	gfx_sendbyte (0x43);
	gfx_sendbyte (x);
	gfx_sendbyte (y);
	gfx_sendbyte (radius);
	gfx_sendbyte (color>>8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a solid circle of radius r
void gfx_disc (unsigned char x, unsigned char y, unsigned char radius, unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	//Set pen size to 0, solid circle
	gfx_sendbyte (0x70);
	gfx_sendbyte (0x00);
	
	gfx_getbyte ();
	
	gfx_sendbyte (0x43);
	gfx_sendbyte (x);
	gfx_sendbyte (y);
	gfx_sendbyte (radius);
	gfx_sendbyte (color>>8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a triangle by joining specific coordinates
void gfx_triangle (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char x3, unsigned char y3, unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x70);		//Wire frame triangle
	gfx_sendbyte (0x01);
	
	gfx_getbyte ();
	
	gfx_sendbyte (0x47);		//Triangle coordinates in anti clockwise fashion
	gfx_sendbyte (x1);
	gfx_sendbyte (y1);
	gfx_sendbyte (x2);
	gfx_sendbyte (y2);
	gfx_sendbyte (x3);
	gfx_sendbyte (y3);
	gfx_sendbyte (color>>8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a bitmap
// Downloads the RGB 5-6-5 format image over the UART connection
//Too slow for most purposes
//Better not use it to write to the entire screen
void gfx_drawbitmap (unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned short *color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte(0x49);
	gfx_sendbyte(x);
	gfx_sendbyte(y);
	gfx_sendbyte(width);
	gfx_sendbyte(height);
	gfx_sendbyte (0x10);
	
	for ( ; height > 0 ; height --)
		for ( ; width > 0 ; width --)
		{
			gfx_sendbyte (*color >> 8);
			gfx_sendbyte(*color);
			color++;
		}
	gfx_getbyte();			//ACK
		
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}
	
// Set background color. The LCD will then default to this color when it is erased
void gfx_setbackcolor (unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x4B);
	gfx_sendbyte (color >> 8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a line with specified parameters
void gfx_line (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x4C);
	gfx_sendbyte (x1);
	gfx_sendbyte (y1);
	gfx_sendbyte (x2);
	gfx_sendbyte (y2);
	gfx_sendbyte (color >> 8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a pixel on the screen with given parameters
void gfx_putpixel (unsigned char x, unsigned char y, unsigned short color)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x50);
	gfx_sendbyte (x);
	gfx_sendbyte (y);
	gfx_sendbyte (color >> 8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw  rectangle with specified parameters
void gfx_rectangle (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned short color, unsigned char type)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x70);
	gfx_sendbyte (type);			//type = SOLID, 0x00 or OUTLINE
	
	gfx_getbyte ();
	
	gfx_sendbyte (0x72);
	gfx_sendbyte (x1);
	gfx_sendbyte (y1);
	gfx_sendbyte (x2);
	gfx_sendbyte (y2);
	gfx_sendbyte (color >> 8);
	gfx_sendbyte (color);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Set the font size to be rendered when using text commands
void gfx_fontsize (unsigned char font)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x46);
	gfx_sendbyte (font);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Set blend mode for the text
// This can be used to write on already rendered images
void gfx_textmode (unsigned char blend)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x4F);
	gfx_sendbyte (blend);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Write formatted text on screen with given setting.
// Previous font formatting functions may also affect this
//so make sure you have already set things right using previous functions
void gfx_formattedtext (unsigned char row, unsigned char col, unsigned char font, unsigned short color, unsigned char *txt)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif

	gfx_sendbyte (0x53);
	gfx_sendbyte (col);
	gfx_sendbyte (row);
	
	gfx_sendbyte (font);
	gfx_sendbyte (color >> 8);
	gfx_sendbyte (color);
	gfx_sendbyte (0x01);
	gfx_sendbyte (0x01);
	
	do
		{
		gfx_sendbyte (*txt);
		txt++;
		}	while (*txt != 0);
	gfx_sendbyte (0);
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

//#####################################################

//################# SD Card Command Set ###############

//#####################################################

// Set the address pointer to the SD card
// Assumes SD card is inserted and properly initialised
// To find out if the functions worked, you can always write the
// error handler inside this routine or return the value returned 
// by the last status read function gfx_getbyte()
void gfx_sd_setaddr (unsigned int addr)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x40);
	gfx_sendbyte (0x41);
	
	gfx_sendbyte ( (unsigned char)(addr>>24));
	gfx_sendbyte ( (unsigned char)((addr<<8)>>24));
	gfx_sendbyte ( (unsigned char)((addr<<16)>>24));
	gfx_sendbyte ( (unsigned char)((addr<<24)>>24));
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Displays an object stored in the memory card at the given address
// Read the Goldelox Documentation for more on this command
void gfx_sd_object (unsigned int addr)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x40);
	gfx_sendbyte (0x4F);
	
	gfx_sendbyte ( (unsigned char)(addr>>24));
	gfx_sendbyte ( (unsigned char)((addr<<8)>>24));
	gfx_sendbyte ( (unsigned char)((addr<<16)>>24));
	gfx_sendbyte ( (unsigned char)((addr<<24)>>24));
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Draw a BMP from the memory card (formatted in RAW)
// Reefer to the documentation for more on this
void gfx_sd_bmp (unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned short addrH, unsigned short addrL)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x40);
	gfx_sendbyte (0x49);
	gfx_sendbyte (x);
	gfx_sendbyte (y);
	gfx_sendbyte (width);
	gfx_sendbyte (height);
	gfx_sendbyte (0x10);		//16-bit color mode
	
	gfx_sendbyte ( lsb16(addrH) );
	gfx_sendbyte ( msb16(addrL) );//Image address, big endian
	gfx_sendbyte ( lsb16(addrL) );
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

// Initiailze the SD card. This routine will fail and will not return an acknowledge byte
// if the SD card is not inserted
void gfx_sd_init (void)
{
	#if (CPU_ACTIVITY == 1)
		CPU_busy;
	#endif
	
	gfx_sendbyte (0x40);
	gfx_sendbyte (0x69);
	
	gfx_getbyte ();
	
	#if (CPU_ACTIVITY == 1)
		CPU_idle;
	#endif
}

//#####################################################

//################## RADIAL coordinate system #########

//#####################################################
//Basic utilities first,
//these are internal functions not defined in the header files and cannot be accessed outside of this

// Gets the deviation from the center coordinate in the form of dx and dy
void radial_getdxdy (unsigned char r, unsigned short phi, signed char *dx, signed char *dy)
{
	if (phi < 90)
	{
		*dx = (r * gfx_cos (phi))/250;
		*dy = (r * gfx_sin (phi))/250;
	}
	else if ((phi >= 90) && (phi < 180))
	{
		phi -= 90;
		*dx = (-1 * r * gfx_sin (phi))/250;
		*dy = (r * gfx_cos (phi))/250;
	}
	else if ((phi >= 180) && (phi < 270))
	{
		phi -= 180;
		*dx = (-1 * r * gfx_cos (phi))/250;
		*dy = (-1 * r * gfx_sin (phi))/250;
	}
	else if ((phi >= 270) && (phi < 361))
	{
		phi -= 270;
		*dx = (r * gfx_sin (phi))/250;
		*dy = (-1 * r * gfx_cos (phi))/250;
	}
	else
	{		//If angle out of bounds
		*dx = 0;
		*dy = 0;
	}
	
}

// Draws a line with the radial coordinate specifications
// Centre is at base_x and base_y
// r1 and phi1 are the radius (in pixels) and angle of the line w.r.t. the X-axis (0-360 degrees)
// Similar for r2 and phi2
void gfx_radial_line (unsigned char base_x, unsigned char base_y, unsigned char r1, unsigned short phi1, unsigned char r2, unsigned short phi2, unsigned short color)
{
 unsigned char x1, x2, y1, y2;
 signed char dx, dy;
	
	radial_getdxdy (r1, phi1, &dx, &dy);
	x1 = base_x + dx;
	y1 = base_y - dy;
	
	radial_getdxdy (r2, phi2, &dx, &dy);
	x2 = base_x + dx;
	y2 = base_y - dy;
	
	gfx_line (x1, y1, x2, y2, color);
}	

//draws a radial circle at the specified polar or radial coordinates
void gfx_radial_circle (unsigned char base_x, unsigned char base_y, unsigned char r1, unsigned short phi1, unsigned char radius, unsigned short color)
{
 unsigned char x1, y1;
 signed char dx, dy;
	
	radial_getdxdy (r1, phi1, &dx, &dy);
	x1 = base_x + dx;
	y1 = base_y - dy;
	
	gfx_circle (x1, y1, radius, color);
}	

// More to come
// If you have added to this file and you think that your conmtribution can be useful
// feel free to upload revision of this file at 
// For queries related to this, you may contact me on
// support@PraikPanda.com
// www.PratikPanda.com
