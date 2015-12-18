#ifndef lotter_c
#define lotter_c

#include <mtlFX.c>

#include "lotter.h"

#include "actor.h"
#include "popman.h"
#include "npc.h"
#include "cam.h"

#include "hud.c"

void lotterLotter ()
{
	while (1)
	{
		snd_play(sfxCrowdCheer2, input_getPopularity() * 10, 0);			
		wait(-(15 - input_getPopularity()));
	}
}

action acLotter ()
{
	g_entLotti = my;
	
	c_updatehull(my, 0);
	lotterLotter();
	
	vec_set(camera->x, my->x);
	
	actorInit(my);
	actorWalkPath(my, "pathLotter", true);
	
	set(my, PASSABLE); //SHADOW | PASSABLE | CAST);
	
	my->ACTOR_WALK_SPEED = 8;
	my->ACTOR_WALK_FAC = 1;
	
	my->ACTOR_WALK_ANIM_SPEED = 7;
	my->ACTOR_IDLE_ANIM_SPEED = 7;
	
	my->ACTOR_WALK_SFX_THRESH = 4;
	
	var frames = 5;
	
	while (1)
	{
		if (frames > 0)
			frames -= 1;
		else
			hud_render();
		
		my->ACTOR_WALK_FAC = 1.5 + sin(total_ticks * 2);
		
		updateCam(my, &g_camType);
		
		wait(1);
	}
}

#endif /* lotter_c */