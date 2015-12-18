#ifndef pnl_c
#define pnl_c

#include "pnl.h"

void pnl_resizeScreen (PANEL* pnl, BOOL setShow)
{
	pnl->pos_x = pnl->pos_y = 0;
	
	pnl->scale_x = screen_size.x / pnl->bmap->width;
	pnl->scale_y = screen_size.y / pnl->bmap->height;
	
	pnl_setShow(pnl, setShow);
}

void pnl_centerX (PANEL* pnl, BOOL setShow)
{
	pnl->pos_x = screen_size.x / 2 - pnl->scale_x * pnl->bmap->width / 2;
	pnl_setShow(pnl, setShow);
}

void pnl_relY (PANEL* pnl, var f, BOOL setShow)
{
	pnl->pos_y = screen_size.y * f - pnl->scale_y * pnl->bmap->height / 2;
	pnl_setShow(pnl, setShow);
}

void pnl_setShow (PANEL* pnl, BOOL setShow)
{
	if (setShow)
		set(pnl, SHOW);
	else
		reset(pnl, SHOW);		
}

#endif /* pnl_c */