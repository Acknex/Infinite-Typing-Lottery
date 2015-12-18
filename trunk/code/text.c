/*
 *******************************************************************************
 * text.c
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */


#include "input.h"

FONT* typewriter_fnt = "parallaxLarge.png";
FONT* typewriter2_fnt = "parallaxLargeDark.png";

TEXT* typewriter_txt =
{
	strings = 2;
	font = typewriter_fnt;
	flags = SHOW;
	layer = 8;
	scale_x = 0.3;
	scale_y = 0.3;
}

TEXT* typewriter2_txt =
{
	strings = 1;
	font = typewriter2_fnt;
	flags = SHOW;
	layer = 9;
	red = 255;
	scale_x = 0.3;
	scale_y = 0.3;
}


//ENTITY* bgEnt;
void text_init()
{
	/*
	bgEnt = ent_createlayer("background.tga", SHOW, 3);
	bgEnt->x = 500;
	bgEnt->y = 0;
	bgEnt->z = -150;
	bgEnt->scale_x = 5;
	bgEnt->scale_y = 0.5;
	*/
	
	set(pnlBgPanel, SHOW);
	
	pnlBgPanel->pos_y = screen_size.y - pnlBgPanel->bmap->height * pnlBgPanel->scale_y + 1;
	pnlBgPanel->size_x = screen_size.x+1;
}

void text_loop()
{	

	var vSizeX = str_width(strFullLine, typewriter_fnt);
	var vSizeY = vSizeX / str_len(strFullLine);
	var vScale = minv(0.5, screen_size.x / vSizeX);
	var vPosX  = maxv(0,(screen_size.x - vSizeX * vScale) * 0.5);
	var vPosY = screen_size.y - 2* vSizeY;
	
	(typewriter_txt->pstring)[0]  = strFullLine;
	(typewriter_txt->pstring)[1]  = strTypedLine;
	(typewriter2_txt->pstring)[0] = strProgressedLine;	
	typewriter_txt->scale_x  = vScale;
	typewriter2_txt->scale_x = vScale;
	typewriter_txt->scale_y  = vScale;
	typewriter2_txt->scale_y = vScale;
	typewriter_txt->pos_x  = vPosX;
	typewriter2_txt->pos_x = vPosX;
	typewriter_txt->pos_y  = vPosY;
	typewriter2_txt->pos_y = vPosY;
}