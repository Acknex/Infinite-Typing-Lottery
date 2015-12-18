#ifndef music_c
#define music_c

#include "music.h"

var musicPlay (SOUND* music, BOOL loop)
{
	var h = 0;
	
	if (loop)
		h = snd_loop(music, g_musicVol, 0);
	else
		h = snd_play(music, g_musicVol, 0);
		
	return(h);
}

void musicFadeOut (var h, var fromVol, var speed)
{
	while (fromVol >= 1)
	{
		snd_tune(h, fromVol, 0, 0);
		
		fromVol -= speed * time_step;
		if (fromVol < 1)
			fromVol = 1;
		
		wait(1);
	}
}

#endif /* music_c */