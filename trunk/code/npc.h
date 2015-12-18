#ifndef npc_h
#define npc_h

#define NPC_PERCENTAGE skill8

var g_npcAmbient = 200;

var g_npcLerchenCount = 0;
var g_npcLerchenPercentage = 100;

action acHaufen ();

void npcPlaceGroundAtVertex (ENTITY* ent, char* filename, EVENT ev, int vertexNr);

void updatePercentageVisibility (ENTITY* ent, var* percent);

void npcJoinPercentage (ENTITY* ent, var* counter);
void npcRegisterPercentage (ENTITY* ent, var* counter);
void npcGetPercentage (ENTITY* ent, var* counter);

#include "npc.c"

#endif /* npc_h */