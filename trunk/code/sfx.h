#ifndef sfx_h
#define sfx_h

var g_sndVol = 100;
var g_sndEntVol = 1000;

SOUND* sfxMenuOpen = "sfxMenuOpen.ogg";

SOUND* sfxClick = "sfxClick.ogg";
SOUND* sfxHoverOff = "sfxHoverOff.ogg";
SOUND* sfxHoverOn = "sfxHoverOn.ogg";

SOUND* sfxGameOpen = "sfxGameOpen.ogg";

SOUND* sfxWalk [2];
SOUND* sfxWalk1 = "sfxWalk1.ogg";
SOUND* sfxWalk2 = "sfxWalk2.ogg";

SOUND* sfxLerche [2];
SOUND* sfxFurz = "sfxFurz.wav";
SOUND* sfxRoeps = "sfxRoeps.wav";

SOUND* sfxCrowdCheer1 = "sfxCrowdCheer1.ogg";
SOUND* sfxCrowdCheer2 = "sfxCrowdCheer2.ogg";

SOUND* sfxFireworkShoot1 = "sfxFireworkShoot1.ogg";
SOUND* sfxFireworkShoot2 = "sfxFireworkShoot2.ogg";
SOUND* sfxFireworkExplode = "sfxFireworkExplode.ogg";

var sfxPlay (SOUND* s);
var sfxEntPlay (ENTITY* ent, SOUND* s, var vol, BOOL loop);

SOUND* sfxRandArr (SOUND** arr, int size);

#include "sfx.c"

#endif /* pnl_h */