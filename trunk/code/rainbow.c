#ifndef rainbow_c
#define rainbow_c

#include "rainbow.h"

action acRainbow ()
{

	npcJoinPercentage(my, &g_npcRainbowCount);
	
	set(my, PASSABLE | INVISIBLE); //SHADOW | PASSABLE | CAST);
	actorWalkPath(my, "pathDoug", true);
	
	my->ACTOR_WALK_SPEED = 10;
	
	while (1)
	{
		g_npcRainbowPercentage = 10 * input_getPopularity();
		updatePercentageVisibility(my, &g_npcRainbowPercentage);
		
		if (!is(my, INVISIBLE))
		{
			VECTOR n;
			vec_set(&n, vector(1, 0, 0));
			vec_rotate(&n, my->pan);
			
			spawnRainbow(vector(my.x, my.x, my.z + 140 + sin(total_ticks * 8) * 140), &n, 5);
		}
		
		wait(1);
	}
}

void pAlphaFadeX(PARTICLE *p)
{
	p.alpha -= time_step * 1;
	if (p.alpha <= 0) p.lifespan = 0;
}

void pRainbowRed(PARTICLE* p)
{
   set(p, MOVE | TRANSLUCENT | LIGHT | BRIGHT);
   vec_set(p.blue, vector(0,0,255));
   p.alpha = 50;
   p.size = RAINBOW_SIZE;
   p.gravity = -0.2;
   p.event = pAlphaFadeX;
}

void pRainbowYellow(PARTICLE* p)
{
   set(p, MOVE | TRANSLUCENT | LIGHT | BRIGHT);
   vec_set(p.blue, vector(0,255,255));
   p.alpha = 50;
   p.size = RAINBOW_SIZE;
   p.gravity = -0.2;
   p.event = pAlphaFadeX;
}

void pRainbowGreen(PARTICLE* p)
{
   set(p, MOVE | TRANSLUCENT | LIGHT | BRIGHT);
   vec_set(p.blue, vector(0,255,0));
   p.alpha = 50;
   p.size = RAINBOW_SIZE;
   p.gravity = -0.2;
   p.event = pAlphaFadeX;
}

void pRainbowBlue(PARTICLE* p)
{
   set(p, MOVE | TRANSLUCENT | LIGHT | BRIGHT);
   vec_set(p.blue, vector(255,0,0));
   p.alpha = 50;
   p.size = RAINBOW_SIZE;
   p.gravity = -0.2;
   p.event = pAlphaFadeX;
}

void pRainbowPurple(PARTICLE* p)
{
   set(p, MOVE | TRANSLUCENT | LIGHT | BRIGHT);
   vec_set(p.blue, vector(255,0,255));
   p.alpha = 50;
   p.size = RAINBOW_SIZE;
   p.gravity = -0.2;
   p.event = pAlphaFadeX;
}

void spawnRainbow(VECTOR* _pos, ANGLE* _dir, int _particleCount)
{
	
	// Mittelpunkt
	VECTOR vecPosition;
	
	vec_set(vecPosition, vector(_pos.x + 0 * RAINBOW_COLOR_DISTANCE, _pos.y, _pos.z));
	vec_rotate(vecPosition, _dir);	
	effect(pRainbowRed, 		_particleCount, vecPosition, vector(0,0,0));
	
	vec_set(vecPosition, vector(_pos.x + cos(_dir.pan + 90) * 1 * RAINBOW_COLOR_DISTANCE, sin(_dir.tilt) + _pos.y, _pos.z));
	effect(pRainbowGreen, 	_particleCount, vecPosition, vector(0,0,0));	
	
	vec_set(vecPosition, vector(_pos.x + cos(_dir.pan + 90) * 2 * RAINBOW_COLOR_DISTANCE, sin(_dir.tilt) + _pos.y, _pos.z));
	effect(pRainbowBlue, 	_particleCount, vecPosition, vector(0,0,0));

	vec_set(vecPosition, vector(_pos.x + cos(_dir.pan + 90) * -1 * RAINBOW_COLOR_DISTANCE, sin(_dir.tilt) + _pos.y, _pos.z));
	effect(pRainbowYellow, 	_particleCount, vecPosition, vector(0,0,0));

	vec_set(vecPosition, vector(_pos.x + cos(_dir.pan + 90) * -2 * RAINBOW_COLOR_DISTANCE, sin(_dir.tilt) + _pos.y, _pos.z));
	effect(pRainbowPurple, 	_particleCount, vecPosition, vector(0,0,0));	
}


#endif /* rainbow_c */