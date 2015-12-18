#ifndef npc_c
#define npc_c

#include "npc.h"
#include "gfx.h"
#include "popman.h"

void npcRegisterPercentage (ENTITY* ent, var* counter)
{
	*counter += 1;
	ent->NPC_PERCENTAGE = *counter;
}

void npcGetPercentage (ENTITY* ent, var* counter)
{
	ent->NPC_PERCENTAGE = 100 * ent->NPC_PERCENTAGE / *counter;
}

void npcJoinPercentage (ENTITY* ent, var* counter)
{
	npcRegisterPercentage(ent, counter);
	wait(1);
	npcGetPercentage(ent, counter);
}

void updatePercentageVisibility (ENTITY* ent, var* percent)
{
	if (ent->NPC_PERCENTAGE > *percent)
		set(ent, INVISIBLE);
	else
		reset(ent, INVISIBLE);
}

action acHaufen ()
{
	my->ambient = g_npcAmbient;
	fx_specBump();
	
	my->pan = random(360);
	my->scale_x = my->scale_y = my->scale_z = 1 + random(2);
	
	c_updatehull(my, 0);
	
	set(my, PASSABLE);
	
	var d = c_trace(my->x, vector(my->x, my->y, my->z - 10000), IGNORE_PASSABLE | USE_POLYGON);
	if (d > 0)
	{
		my.z = hit.z;
	}
	
	wait(-5);
	
	while (my->scale_x > 0.1)
	{
		var s = my->scale_x - time_step * 0.1;
		my->scale_x = my->scale_y = my->scale_z = s;
		
		wait(1);
	}
	
	ptr_remove(my);
}

void npcPlaceGroundAtVertex (ENTITY* ent, char* filename, EVENT ev, int vertexNr)
{
	CONTACT c;
	ent_getvertex(ent, &c, vertexNr);
	
	VECTOR pos;
	vec_set(&pos, c.x);
	vec_rotate(&pos, ent->pan);
	vec_add(&pos, ent->x);
	
	ent_create(filename, &pos, ev);
}

action acLerche ()
{
	npcJoinPercentage(my, &g_npcLerchenCount);
	
	var s = 1 + random(1);
	my->scale_x = my->scale_y = my->scale_z = s;
	c_updatehull(my, 0);

	actorInit(my);
	
	set(my, PASSABLE); //SHADOW | PASSABLE | CAST);
	actorWalkPath(my, "pathLerche", true);
	
	my->ACTOR_WALK_SPEED = 8;
	my->ACTOR_WALK_FAC = 1;
	
	my->ACTOR_WALK_ANIM_SPEED = 7;
	my->ACTOR_IDLE_ANIM_SPEED = 7;
	
	my->ACTOR_WALK_SFX_THRESH = 4;
	
	var sfxInterval = 5 * 16;
	var sfxTimer = random(sfxInterval);
	
	while (1)
	{
		my->ACTOR_WALK_FAC = 1 + sin(total_ticks * 2);
	
		if (sfxTimer < 0)
		{
			sfxTimer += sfxInterval;
			
			if (!is(my, INVISIBLE))
			{
				
				SOUND* snd = sfxRandArr(sfxLerche, 2);
				sfxEntPlay(my, snd, 600);
				
				if (snd == sfxFurz)
				{
					effVertexNormal(effFart, 20, my, 165);
					npcPlaceGroundAtVertex(my, "oKacke.mdl", acHaufen, 165);
				}
					
				if (snd == sfxRoeps)
				{
					effVertexNormal(effBurp, 20, my, 378);
					npcPlaceGroundAtVertex(my, "oKotze.mdl", acHaufen, 378);
				}
			}
		}
		else
			sfxTimer -= time_step;
		
		g_npcLerchenPercentage = 10 * input_getPopularity();
		updatePercentageVisibility(my, &g_npcLerchenPercentage);
		
		wait(1);
	}
}

#endif /* npc_c */