#ifndef gfx_h
#define gfx_h

#define FIREWORK_SCALE 0.5

var g_npcAvatarCount = 0;
var g_npcAvatarPercentage = 100;

BMAP* pFartBurp = "pFartBurp.tga";

void effVertexNormal (EVENT ev, int num, ENTITY* ent, int vertexNr);

void effBurp (PARTICLE* p);
void effFart (PARTICLE* p);
void effAlphaFade (PARTICLE *p);

#include "gfx.c"

#endif /* gfx_h */