#ifndef terrain_c
#define terrain_c

#include <mtlFx.c>
#include "terrain.h"

#include "popman.h"

#include "terrainseed.c"
#include "game.h"

action acTerrain ()
{
	my->clipfactor = 99999;
	my->ambient = g_terrainAmbient;	
	
	//fx_specBump();
	
	//reset(my, DYNAMIC);
	
	my->material = mtl_terrain;
	effect_load(my->material, "terrainanim.fx");
	
	/*
	TERRAIN_SEED_SETTINGS settings;
	
	settings.model[0] = "oGlocke.mdl"; //B
	settings.model[1] = "oGrass.mdl"; //G
	settings.model[2] = "oMushroom.mdl"; //R
	settings.modelMat[0] = mtlAlphatest;
	settings.modelMat[1] = mtlAlphatest;
	settings.modelMat[2] = mtlAlphatest;
	vec_set(settings.terrainSize, vector(7800, 7000, 0));
	vec_set(settings.baseRate, vector(30, 30, 5));
	vec_set(settings.maxOffset, vector(8, 8, 8));
	vec_set(settings.modelScale, vector(1, 1, 1));
	settings.vertexLimit = 32000;
	
	seed_terrain(my, wBlendmap, &settings);	
	*/
	
	float b = 0;
	float c = 2;
	var bass;

	while (1)
	{
		bass = g_bass;
		bass = maxv(bass-15, 0);
		
		if(bass > 3.0)
		{
			b = 0.0;
		}
		
		my.skill41 = floatv(bass/5);
		my.skill42 = floatv(b*0.03);
		
		b += time_step*0.5;
		
		wait(1);
	}
}

action acRocks ()
{
	//my->material = mtl_specBump;
	my->ambient = g_terrainAmbient;
	my->clipfactor = 99999;
	
	//fx_specBump();
	
	//reset(my, DYNAMIC);
	
	my->material = mtl_terrain;
	effect_load(my->material, "terrainanim.fx");
	
	float b = 0;
	float c = 2;
	var bass;

	while (1)
	{
		bass = g_bass;
		bass = maxv(bass-15, 0);
		
		if(bass > 3.0)
		{
			b = 0.0;
		}
		
		my.skill41 = floatv(bass/10);
		my.skill42 = floatv(b*0.05);
		
		b += time_step*0.5;
		
		wait(1);
	}	
}

action acStatObj ()
{
	my->material = mtl_specBump;
	my->ambient = g_terrainAmbient;
	
	set(my, PASSABLE);
	
	fx_specBump();
	
	reset(my, DYNAMIC);
}

action acSpinObj ()
{
	my->material = mtl_specBump;
	my->ambient = g_terrainAmbient;
	
	fx_specBump();
	
	set(my, PASSABLE);
	
	while (1)
	{
		my->pan = sin(total_ticks * 2) * 360;
		my->tilt = cos(total_ticks * 2 + 90) * 180;
		
		wait(1);
	}
}

action acPlatane ()
{
	npcJoinPercentage(my, &g_npcPlataneCount);

	my->material = mtl_specBump;
	my->ambient = g_terrainAmbient;
	
	fx_specBump();
	
	set(my, PASSABLE);
	
	var height = my.z;
	my->pan = random(360);
	
	while (1)
	{
		my->z = height + sin((total_ticks + my.x) * 4 + my.y) * 50;
		my->pan += 5 * time_step;
		my->tilt = sin(total_ticks * 3) * 15;
		
		g_npcPlantagePercentage = 10 * input_getPopularity();
		updatePercentageVisibility(my, &g_npcPlantagePercentage);
		
		wait(1);
	}
}

action acTribune ()
{
	my->ambient = g_terrainAmbient;
	set(my, PASSABLE);
	fx_specBump();
	
	while (1)
	{
		if (input_getPopularity() >= 2)
			sfxEntPlay(my, sfxCrowdCheer1, 2000);
			
		wait(-3);
	}
}

action acGrass ()
{
	set(my, PASSABLE | OVERLAY);
	reset(my, DYNAMIC);
	
	my->ambient = 200;
}

#endif /* terrain_c */