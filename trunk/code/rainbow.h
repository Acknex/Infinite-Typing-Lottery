#ifndef rainbow_h
#define rainbow_h

#define RAINBOW_SIZE 40
#define RAINBOW_COLOR_DISTANCE 5
#define RAINBOW_COUNT 1

var g_npcRainbowCount = 0;
var g_npcRainbowPercentage = 100;

void spawnRainbow(VECTOR* _pos, ANGLE* _dir, int _particleCount);

#include "rainbow.c"

#endif /* rainbow_h */