#ifndef music_h
#define music_h

var g_musicVol = 100;

SOUND* mMenu = "mMenu.ogg";

var musicPlay (SOUND* music, BOOL loop);

void musicFadeOut (var h, var fromVol, var speed);

#include "music.c"

#endif /* music_h */