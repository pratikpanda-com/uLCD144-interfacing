/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : goldelox_interface.c                                             *
* Description : Hardware routines for UART communication. Change this while   *
*    			porting this code for other platforms                       *
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
#include "goldelox_interface.h"

void delay_us (unsigned int i)	//Rough delay period
{
	unsigned int c;
	for ( ; i>0 ; i--)
		for ( c=0; c<=35; c++);
}

//Initialize the UART hardware.
// You need to modify this if you are using an MCU of your choice
void gfx_interface_init (void)
{
  delay_us (500000);			//0.5 s delay before initialising LCD
  PINSEL0 = 0x00050000;           
  U1LCR = 0x83; 				//8 bit, no parity, one stop bit, 115200 bps, 15 MHz VPB
  U1DLL = 97;    
 // U1FDR = 0xC2;
  U1LCR = 0x03;                   // DLAB = 0
}

// Transmit a byte, MSB first
void gfx_sendbyte (unsigned char cmd)
{
  while (!(U1LSR & 0x20));
  U1THR = cmd;
}

//Receive a byte
unsigned char gfx_getbyte (void)	
{
  while (!(U1LSR & 0x01));
  return (U1RBR);
}

