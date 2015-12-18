#ifndef start_c
#define start_c

#include "start.h"

#include "game.h"
#include "pnl.h"
#include "music.h"
#include "sfx.h"

void acStartBut ()
{
	VECTOR offset;
	
	while (is(pStartBut, SHOW))
	{
		offset.x = sin(0.25 * total_ticks) * 40;
		offset.y = cos(0.5 * total_ticks + 90) * 20;
		offset.z = 1 + sin(0.25 * total_ticks) * 0.25;
		
		pStartBut->scale_x = pStartBut->scale_y = offset.z;
		
		pnl_centerX(pStartBut, true);
		pnl_relY(pStartBut, 0.75, true);
		
		pStartBut->pos_x += offset.x;
		pStartBut->pos_y += offset.y;
		
		wait(1);
	}
}

void openStart ()
{
	mouse_map = bCursor;
	mouse_mode = 4;
	
	pnl_resizeScreen(pStart, true);
	
	sfxPlay(sfxMenuOpen);
	
	set(pStartBut, SHOW);
	acStartBut();
	
	var mH = musicPlay(mMenu, true);
	
	while (!g_startGo) wait(1);
	
	pnl_setShow(pStartBut, false);
	
	musicFadeOut(mH, g_musicVol, 5);
	
	wait(-2);
	
	var sH = sfxPlay(sfxClick);
	
	openGame();
	
	wait(3);
	
	pnl_setShow(pStart, false);
}

void pStartButOnEv ()
{
	g_startGo = true;
	mouse_mode = 0;
}

void pStartButOffEv ()
{
	sfxPlay(sfxHoverOff);
}

void pStartButOverEv ()
{
	sfxPlay(sfxHoverOn);
}

#endif /* start_c */