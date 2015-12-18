#ifndef _TERRAINSEED_C_
#define _TERRAINSEED_C_

#include "DynamicModels.h"

typedef struct 
{
	STRING *model[3];		// Model files
	var baseRate[3];		// Base model placing probability
	var maxOffset[3];		// Maximum offset in xy-distance from vertex position
	var modelScale[3];		// xyz-scale of the placed entity
	MATERIAL *modelMat[3];	// Material of the placed entity
	VECTOR terrainSize;		// Size of the terrain
	int vertexLimit;		// Vertex limit per merged mesh
} TERRAIN_SEED_SETTINGS;

/// 
/// Seeds entities to a terrain 
/// 
/// ent			= Terrain entity
/// mask		= Seeding texture, red channel = seeding probability
/// settings	= Settings which determine model placement
///

void seed_terrain(ENTITY *ent, BMAP *mask, TERRAIN_SEED_SETTINGS *settings)
{
	int i;
	int j;
	
	DynamicModels_Settings.flags = DYNAMIC_MODELS_FIXNORMALS | DYNAMIC_MODELS_OPTIMIZE | DYNAMIC_MODELS_CLONE_TEX;
	
	DYNAMIC_MODEL *seedModel[3];
	ENTITY *seedEnt[3];
	
	for(j = 0; j < 3; j++)
	{
		seedEnt[j] = ent_create(settings->model[j], nullvector, NULL);
		seedModel[j] = DynamicModel_Create();
		seedModel[j]->skin[0] = ent_getskin(seedEnt[j], 1);
		seedModel[j]->skin[1] = ent_getskin(seedEnt[j], 2);
	}
	
	var maskWidth = bmap_width(mask);
	var maskHeight = bmap_height(mask);
	var format = bmap_lock(mask, 0);
	
	var x,y;
	var w, h;
	w = settings->terrainSize.x / 2;
	h = settings->terrainSize.y / 2;
	
	for(x = -w; x <= w; x += 100) for(y = -h; y <= h; y += 100)
	{
		var color[3]; color[0] = color[1] = color[2] = 0;
		var alpha = 0;
		
		VECTOR pos;
		if(!c_trace(vector(x,y, 1000), vector(x,y, -1000), IGNORE_PASSABLE | IGNORE_PASSENTS | USE_POLYGON))
			continue;
		if(you != ent)
			continue;
		
		vec_set(pos, target);
		
		var tx = (maskWidth-1)  * ((x + w) / settings.terrainSize.x);
		var ty = (maskHeight-1) * ((y + h) / settings.terrainSize.y);
		
		tx = clamp(tx, 0, maskWidth-1);
		ty = clamp(ty, 0, maskHeight-1);
		
		pixel_to_vec(color, &alpha, format, pixel_for_bmap(mask, tx, ty));
		
		for(j = 0; j < 3; j++)
		{
			vec_set(&(seedEnt[j]->x), &pos);
			seedEnt[j]->x += random(settings->maxOffset[j]) - random(settings->maxOffset[j]/2);
			seedEnt[j]->y += random(settings->maxOffset[j]) - random(settings->maxOffset[j]/2);
			seedEnt[j]->pan = random(360);
			vec_fill(&(seedEnt[j]->scale_x), settings->modelScale[j]);
			
			if(random(100) >= settings->baseRate[j])
				continue;
			
			if(random(256) >= color[j])
				continue;
			
			DynamicModel_AddEntity(seedModel[j], seedEnt[j]);
			
			if(seedModel[j]->vertexCount >= settings->vertexLimit)
			{
				you = DynamicModel_CreateInstance(seedModel[j], nullvector, NULL);
				if(you)	you->material = settings->modelMat[j];
				DynamicModel_Delete(seedModel[j]);
				seedModel[j] = DynamicModel_Create();
				seedModel[j]->skin[0] = ent_getskin(seedEnt[j], 1);
				seedModel[j]->skin[1] = ent_getskin(seedEnt[j], 2);
			}
		}
	}
	bmap_unlock(mask);

	for(j = 0; j < 3; j++)
	{
		you = DynamicModel_CreateInstance(seedModel[j], nullvector, NULL);
		if(you)	you->material = settings->modelMat[j];
		DynamicModel_Delete(seedModel[j]);
		
		ent_remove(seedEnt[j]);
	}
}

#endif // #ifndef _TERRAINSEED_C_