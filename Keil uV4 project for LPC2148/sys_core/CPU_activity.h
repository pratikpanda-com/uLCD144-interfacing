/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : CPU_activity.h                                                   *
* Description : Routines to use the "busy" LED. Helps in debugging            *
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

#ifndef _CPU_ACTIVITY_H_
	#define _CPU_ACTIVITY_H_
	
#include <LPC214x.h>

#define		cpu_led_port_dir	IO0DIR
#define		cpu_led_port_num	25				//Port 0.25 as busy LED - active LOW
#define		cpu_led_port_set	IO0SET

#define		CPU_busy	{IO0CLR = (1<<cpu_led_port_num);}		//insert to light up BUSY LED
#define		CPU_idle	{IO0SET = (1<<cpu_led_port_num);}

#define		CPU_ACTIVITY		1				// 1=enable, 0 = disable the busy LED feature

void init_CPU_busy_LED (void);
	
#endif
