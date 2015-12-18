#ifndef seedX_c
#define seedX_c

#include "seedX.h"
#include "game.h"

void acFlower ()
{
	set(my, PASSABLE);
	my->ambient = g_npcAmbient;
	fx_specBump();	
	
	wait(1);
	
	vec_scale(my->scale_x, 1 + random(4));
	c_updatehull(my, 0);
	
	my->x += -32 + random(64);
	my->y += -32 + random(64);
	
	my->pan = random(360);
	
	var d = c_trace(my->x, vector(my->x, my->y, my->z - 10000), IGNORE_PASSABLE | USE_POLYGON);
	if (d > 0)
	{
		my.z = hit.z - my->min_z;
	}
	
	reset(my, DYNAMIC);
}

action acFlowerSeed ()
{
	wait(1);
	
	int i;
	
	for (i = 0; i < ent_status(my, 0); i++)
	{
		CONTACT c;
		ent_getvertex(my, &c, i+1);
		
		VECTOR pos;
		vec_set(&pos, c.x);
		vec_scale(&pos, my->scale_x);
		vec_add(&pos, my->x);
		
		ENTITY* e = ent_create("oGlocke.mdl", &pos, acFlower);		
	}
	
	ptr_remove(my);
}

#endif /* seedX_c */