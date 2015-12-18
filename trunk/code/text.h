/*
 *******************************************************************************
 * text.h
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */

#ifndef TEXT_H
#define TEXT_H

void text_init();
void text_loop();

PANEL* pnlBgPanel =
{
	bmap = "bgPanel.tga";
	flags = FILTER;
	layer = 0;
	scale_y = 0.625;
}

#include "text.c"

#endif