/*****************************************************************************\
*              Goldelox SGC uLCD-144 driver library for LPC214x               *
*          --------------------- -----------------------------------          *
*                                                                             *
* Filename : graphics_objects.h                                               *
* Description : Some graphics objects as examples, using core commands        *
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

#ifndef _GRAPHICS_OBJECTS_H_
#define _GRAPHICS_OBJECTS_H_

#define 	HISTOGRAM_SOLID				0
#define 	HISTOGRAM_LINE				1
#define	MAX_HISTOGRAM_DIVISIONS			60			//For 120px wide histogram


//############################################ COMMAND LINE OBJECT #######################################################
typedef struct cmdline_obj
{
	unsigned char font_size;	//font_size = TEXT_SMALL, TEXT_MEDIUM, TEXT_LARGE
	unsigned char x;			//Starting corner x
	unsigned char y;			//Starting corner y
	unsigned char cols;		//Width of text window
	unsigned char lines;		//Height of text window
	unsigned short font_color;
	unsigned short back_color;
	unsigned char opacity;
}cmdline_obj;
	
//############################################ HISTOGRAM OBJECT ##########################################################

typedef struct	histogram_obj{
	unsigned char data [MAX_HISTOGRAM_DIVISIONS];	//Data for graph, points to be plotted. data[0] is at origin
//	unsigned char divisions;	//Divisions along x-axis
	unsigned short plot_color;	//Color of graph
	unsigned short axis_color;	//Color of axes
	unsigned short background;	//Background color
	unsigned char height;		//Height of histogram
	unsigned char width;		//Width of histogram
	unsigned char x;			//x and y are origin coordinates
	unsigned char y;
	unsigned char type;			//HISTOGRAM_SOLID or HISTOGRAM_LINE
}histogram_obj;
	
void histogram_initialize (histogram_obj *hist);
void histogram_update (histogram_obj *hist);

void cmdline_initialize (struct cmdline_obj *cmd);
void cmdline_render (cmdline_obj *cmd);
void cmdline_update (unsigned char *txt, unsigned char line, cmdline_obj *cmd);

#endif
