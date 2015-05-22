/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : main.c                                                           *
* Description : main file                                                     *
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

#include "Goldelox/goldelox_core.h"
#include "Goldelox/graphics_objects.h"
#include "sys_core/CPU_activity.h"
#include "sys_graphics/img_addr.h"

#include "apps/app_test.h"

void delay (unsigned int i)
{
	unsigned int c;
	for ( ; i>0 ; i--)
		for ( c=0; c<=35; c++);
}

int main ()
{
	#if (CPU_ACTIVITY == 1)
		init_CPU_busy_LED ();
		CPU_idle;
	#endif
	delay(100000);				//Let power stabilize before auto-bauding with display
	gfx_boot();
	gfx_sd_init ();
	
	//#################### Code starts here, SD and disp turned on and ready ###################
	
	app_test ();				//Plays the demo application
		
	while (1);
}

