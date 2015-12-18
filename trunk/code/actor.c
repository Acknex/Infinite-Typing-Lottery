#ifndef actor_c
#define actor_c

#include "actor.h"

void assertMipMaps (ENTITY* ent)
{
	int i;
	for (i = 0; i < ent_status(ent, 8); i++)
		ent_setskin(ent, bmap_to_mipmap(ent_getskin(ent, i+1)), i+1);
}

void actorSetShadow (ENTITY* ent, BOOL noSelfShadow)
{
	set(ent, SHADOW);
	
	if (noSelfShadow)
		set(ent, CAST);
}

var actorAttachNextPath (ENTITY* ent, char* pathname)
{
	path_set(ent, pathname);
}

void actorInit (ENTITY* ent)
{
	my->material = mtl_specBump;
	my->ambient = g_actorAmbient;
}

void actorWalkPath (ENTITY* ent)
{
	actorWalkPath(ent, false);
}

void actorWalkPath (ENTITY* ent, BOOL randomPathPos)
{
	actorWalkPath(ent, ent->string1, randomPathPos);
}

void actorWalkPath (ENTITY* ent, char* pathname, BOOL randomPathPos)
{
	if (actorAttachNextPath(ent, pathname) == 0)
		error(str_printf(NULL, "actorWalkPath for %s: no path found!", ent->type));
	else
	{
		var length = path_length(ent);
		
		var dist = 0;
		if (randomPathPos)
			dist = random(length);
		
		var anim = random(100);
		ent->ACTOR_WALK_SFX_TIMER = anim/100 * ent->ACTOR_WALK_SFX_THRESH;
		
		VECTOR oldPos;
		vec_set(&oldPos, my->x);
		
		while (1)
		{
			VECTOR pos;
			path_spline(ent, &pos, dist);
		
			var m = ent->scale_x * ent->ACTOR_WALK_SPEED * ent->ACTOR_WALK_FAC;
			dist = (dist + m * time_step) % length;
			
			vec_set(ent->x, &pos);
			
			VECTOR from;			
			vec_set(&from, ent->x);
			from.z = 1024;
			
			VECTOR to;
			vec_set(&to, ent->x);
			to.z = -256;
			
			var mode = (IGNORE_PASSABLE | IGNORE_SPRITES | USE_POLYGON);
			var d = c_trace(&from, &to, mode);
			
			if (d > 0)
			{
				ent->z = hit->z - ent->min_z;
			}
			
			if (ent->ACTOR_WALK_FAC > 0.1)
			{
				anim = (anim + ent->ACTOR_WALK_ANIM_SPEED * ent->ACTOR_WALK_FAC * ent->scale_x * time_step) % 100;
				ent_animate(ent, "walk", anim, ANM_CYCLE);
			}
			else
			{
				anim = (anim + ent->ACTOR_IDLE_ANIM_SPEED * time_step) % 100;
				ent_animate(ent, "stand", anim, ANM_CYCLE);
			}
			
			VECTOR v;
			vec_diff(&v, my->x, &oldPos);
			
			vec_to_angle(my->pan, &v);
			my->roll = 0;
			
			vec_lerp(&oldPos, &oldPos, my->x, 0.1 * time_step);
			
			ent->ACTOR_WALK_SFX_TIMER += time_step * ent->ACTOR_WALK_FAC;
			if (ent->ACTOR_WALK_SFX_TIMER > ent->ACTOR_WALK_SFX_THRESH)
			{
				ent->ACTOR_WALK_SFX_TIMER -= ent->ACTOR_WALK_SFX_THRESH;
				
				if (!is(my, INVISIBLE))
					sfxEntPlay(ent, sfxWalk[ent->ACTOR_WALK_SFX_INDEX], 500);
				
				ent->ACTOR_WALK_SFX_INDEX = (ent->ACTOR_WALK_SFX_INDEX + 1) % 2;
			}
			
			wait(1);
		}
	}	
}

#endif /* actor_c */