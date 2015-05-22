/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : graphics_objects.c                                               *
* Description : Some graphics objects derived from basic functions            *
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

#include "graphics_objects.h"
#include "goldelox_core.h"

void cmdline_initialize (struct cmdline_obj *cmd)
{
	cmd->font_size 	= gfx_SMALL;						//Currently only small font support by the blocks of code below
	cmd->x		= 0;
	cmd->y		= 0;
	cmd->cols		= 20;
	cmd->lines		= 15;
	cmd->font_color 	= 0xFFFF;
	cmd->back_color 	= 0x0000;
	cmd->opacity	= gfx_TRANSPARENT;
}

void cmdline_render (struct cmdline_obj *cmd)				//Render the command line
{
	if (cmd->opacity != gfx_TRANSPARENT)				//Create window for text
		gfx_rectangle (cmd->x, cmd->y, cmd->x + cmd->cols*6, cmd->y + cmd->lines*8, cmd->back_color, gfx_SOLID);
		
	gfx_rectangle (cmd->x, cmd->y, cmd->x + 2, cmd->lines * 8, ~cmd->back_color, gfx_SOLID);
}

void cmdline_update (unsigned char *txt, unsigned char line, struct cmdline_obj *cmd)		//Update already rendered command line
{
	gfx_fontsize (cmd->font_size);
	gfx_textmode (cmd->opacity);
	
	gfx_formattedtext (cmd->y + line*8, cmd->x + 4, gfx_SMALL, cmd->font_color, txt);
}

void histogram_initialize (struct histogram_obj *hist)
{
	unsigned char i;
	
	for (i=0; i <= MAX_HISTOGRAM_DIVISIONS; i++)
		hist->data[i] = 0;
		
//	hist->divisions  = 60;								//Initially 20 values on X-axis
	hist->plot_color = rgb(20, 30, 31);					//Bluish color of graph
	hist->axis_color = 0xFFFF;							//White axes
	hist->background = 0x0000;							//Black background
	hist->height	 = 50;								//50px height of histogram
	hist->width		 = 120;								//128px width
	hist->x		 = 3;								//Initial x, better change this in main program as you need
	hist->y		 = 120;								//From upper right corner of screen, which is (0,0)
	hist->type   	 = HISTOGRAM_LINE;					//Solid fill
}

void histogram_update (histogram_obj *hist)		//Use this to update histogram to new state on display
{
 unsigned char i, x_coordinate;
	
	
	for (i = 0; i < MAX_HISTOGRAM_DIVISIONS; i++)
	{
			x_coordinate = ((hist->width/MAX_HISTOGRAM_DIVISIONS) * i) + hist->x;

		gfx_rectangle ( x_coordinate, hist->y - hist->data[i], x_coordinate/2 , hist->y, hist->plot_color, HISTOGRAM_SOLID);
}
}
