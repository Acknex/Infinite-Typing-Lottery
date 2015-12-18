#ifndef start_h
#define start_h

BOOL g_startGo = false;

void pStartButOnEv ();
void pStartButOffEv ();
void pStartButOverEv ();

BMAP* bCursor = "bCursor.tga";

PANEL* pStart =
{
	bmap = "pStart.tga";
	flags = FILTER;
}

PANEL* pStartBut =
{
	bmap = "pStartBut.tga";
	button(0, 0, "pStartBut.tga", "pStartBut.tga", "pStartButT.tga", pStartButOnEv, pStartButOffEv, pStartButOverEv);
	
	flags = FILTER;
	
	layer = 1;
}

void openStart ();

#include "start.c"

#endif /* start_h */