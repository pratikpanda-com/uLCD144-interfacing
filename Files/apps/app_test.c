/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : app_test.c                                                       *
* Description : A test application of the library as an example               *
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

#include <LPC214x.h>
#include "../sys_graphics/img_addr.h"
#include "../Goldelox/goldelox_core.h"
#include "app_test.h"

// A simple function to test various graphics functions.
// In this example, it creates a flower like pattern based on the radial
// coordinate functions and plots that on the display.
// The angle slowly varies from 0 to 360 degrees and the radial lines are
// of random lengths. Each line is tipped with a small circle

void app_test (void)
{
	unsigned short phi;
	unsigned char radius = 5;
	unsigned int i, x;
		
	unsigned int random_seed = 961;

	while(1)
	{
		for (phi = 0; phi < 360; phi +=3)
		{
			gfx_radial_line (64, 64, 0, 0, x, phi, rgb (30, 5, 5));		//Radial line
			gfx_radial_circle (64, 64, x, phi, 2, rgb (0, 0, 30));		//Tip of radial lines

		for (i=0; i<1000000; i++);								//Some delay
		
	  random_seed = random_seed * 1103515245 +12345;   
	  x = 12*(random_seed / 65536) % 32768;
		x = x % 60;
	
		}
	}
}
