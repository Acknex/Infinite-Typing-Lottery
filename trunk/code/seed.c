#ifdef seed_c
#define seed_c

#include "seed.h"

void acSeededStatic ()
{
	set(my, PASSABLE);
	
	error("1");
	
	var d = c_trace(my->x, vector(my->x, my->y, my->z - 10000), IGNORE_PASSABLE | USE_POLYGON);
	if (d > 0)
	{
		my.z = hit.z;
		error("2");
	}
	
	//my->ambient = g_npcAmbient;
	//fx_specBump();
}

action acFlowerSeed ()
{
	wait(1);
	
	int i;
	
	error("?");
	
	for (i = 0; i < ent_status(my, 0); i++)
	{
		
		error("!!!");
		
		CONTACT c;
		ent_getvertex(my, &c, i+1);
		
		VECTOR pos;
		vec_set(&pos, c.x);
		vec_scale(&pos, my->scale_x);
		vec_add(&pos, my->x);
		
		ENTITY* e = ent_create("oGlocke.mdl", &pos, acSeededStatic);		
	}
}

#endif /* seed_c */