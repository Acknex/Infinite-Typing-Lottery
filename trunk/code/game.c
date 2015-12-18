#ifndef game_c
#define game_c

#include "game.h"
#include "sfx.h"
#include "sky.h"

#include <shadows.c>

#include "lotter.h"

#include "modplay.h"

#include "input.h"
#include "text.h"

void openGame ()
{
	level_load("world.wmb");
	
	skychange();
	sfxPlay(sfxGameOpen);
	
	music_start();
	text_init();
	input_init();
	input_enable();
	
	
	while (1)
	{
		g_bass = music_processChannel(); // 0...10000
		
		input_loop();
		text_loop();
		
		wait(1);
	}
}

#endif /* game_c */