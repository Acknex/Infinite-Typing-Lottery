#ifndef terrain_h
#define terrain_h

var g_npcPlataneCount = 0;
var g_npcPlantagePercentage = 100;

var g_terrainAmbient = 200;

action acTerrain ();
action acRocks ();

BMAP* wBlendmap = "wBlendmap.tga";

MATERIAL* mtlAlphatest = 
{ 
  effect =
  "
    technique alpha_test
    {
      pass p0
      {
        zWriteEnable = true;
        alphaTestEnable = true;
        alphaBlendEnable = false;
      }
    }
  ";
}

#include "terrain.c"

#endif /* terrain_h */