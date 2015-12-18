#ifndef sfx_c
#define sfx_c

#include "sfx.h"

void sfx_h_startup ()
{
	sfxWalk[0] = sfxWalk1;
	sfxWalk[1] = sfxWalk2;

	sfxLerche[0] = sfxFurz;
	sfxLerche[1] = sfxRoeps;
}

var sfxPlay (SOUND* s)
{
	return(snd_play(s, g_sndVol, 0));
}

var sfxEntPlay (ENTITY* ent, SOUND* s, var vol)
{
	return(sfxEntPlay(ent, s, vol, false));
}

SOUND* sfxRandArr (SOUND** arr, int size)
{
	return(arr[(int)random((var)size)]);
}

var sfxEntPlay (ENTITY* ent, SOUND* s, var vol, BOOL loop)
{
	var h = 0;
	
	if (!loop)
		h = ent_playsound(ent, s, vol);
	else
		h = ent_playloop(ent, s, vol);
		
	return(h);
}

#endif /* sfx_c */