#ifndef gfx_c
#define gfx_c

#include "gfx.h"
#include "popman.h"
#include "npc.h"
#include "input.h"

action acAvatar ()
{
	npcJoinPercentage(my, &g_npcAvatarCount);
	
	var height = my.z;
	var offset = random(360);
	
	set(my, PASSABLE);
	reset(my, OVERLAY);
	
	my->pan = 0;
	
	my->ambient = 128;
	
	while (1)
	{
		my.z = height + sin((total_ticks + offset) * 8) *`16;
		my.scale_x = my.scale_y = 1 + sin((total_ticks + offset) * 4) *`0.2;
		
		g_npcAvatarPercentage = 10 * input_getPopularity();
		updatePercentageVisibility(my, &g_npcAvatarPercentage);		
		
		wait(1);
	}
}

void effVertexNormal (EVENT ev, int num, ENTITY* ent, int vertexNr)
{
	CONTACT c;
	ent_getvertex(ent, &c, vertexNr);
	
	VECTOR pos;
	vec_set(&pos, c.x);
	vec_rotate(&pos, ent->pan);
	vec_scale(&pos, ent->scale_x);
	vec_add(&pos, ent->x);
	
	VECTOR n;
	vec_set(&n, c.nx);
	vec_rotate(&n, ent->pan);
	vec_scale(&n, 5 + random(10));
		
	effect(ev, num, &pos, &n);
}

void effBurp (PARTICLE* p)
{
	VECTOR vecTemp;
	vec_set(vecTemp, vector(0,0,-1+random(2)));
   vec_add(p.vel_x,vecTemp);
   vec_rotate(p.vel_x, vector(-45+random(90), -45+random(90), 0));
   
   set(p, MOVE | TRANSLUCENT | LIGHT);
   vec_set(p.blue, vector(0,255,0));
   p.bmap = pFartBurp;
   p.alpha = 25+random(25);
   p.size = 20+random(50);
   p.gravity = random(4);
   p.event = effAlphaFade;
}

void effFart (PARTICLE* p)
{
	VECTOR vecTemp;
	vec_set(vecTemp, vector(0,0,-1+random(2)));
   vec_add(p.vel_x,vecTemp);
   vec_scale(p.vel_x, random(2));
   vec_rotate(p.vel_x, vector(-45+random(90), -45+random(90), 0));
   set(p, MOVE | TRANSLUCENT | LIGHT);
   vec_set(p.blue, vector(60,60,64));
   p.bmap = pFartBurp;
   p.alpha = 25+random(25);
   p.size = 30+random(50);
   p.gravity = -random(4);
   p.event = effAlphaFade;
}

void effAlphaFade (PARTICLE *p)
{
	p.alpha -= time_step * 4;
	p.size += 5 * time_step;
	if (p.alpha <= 0) p.lifespan = 0;
}

void effAlphaFade2 (PARTICLE *p)
{
	p.alpha -= time_step * 4;
	if (p.alpha <= 0) p.lifespan = 0;
}

void pFirework(PARTICLE* p)
{
	VECTOR vecTemp;
	vec_set(vecTemp, vector(-5 + random(10),-5+random(10),random(5)));
   vec_add(p.vel_x,vecTemp);
   set(p, MOVE | TRANSLUCENT | LIGHT);
   vec_set(p.blue, vector(random(255),random(255),random(255)));
   p.alpha = 100;
   p.size = 6+random(3);
   p.gravity = -0.2;
   p.event = effAlphaFade2;
}

void pFireworkExplosion(PARTICLE* p)
{
	VECTOR vecTemp;
	vec_set(vecTemp, vector(-10 + random(20),-10+random(20),-5 + random(10)));
   vec_add(p.vel_x,vecTemp);
   set(p, MOVE | TRANSLUCENT | LIGHT);
   vec_set(p.blue, vector(0,200+random(50),200+random(50)));
   p.alpha = 100;
   p.size = 2+random(3);
   p.gravity = -0.2;
   p.event = effAlphaFade2;
}

void shootFireworkComplex (ENTITY* src, VECTOR* _start, int _complex)
{
	if (integer(random(2)) == 1)
		sfxEntPlay(src, sfxFireworkShoot1, 500, false);
	else
		sfxEntPlay(src, sfxFireworkShoot2, 500, false);
		
	VECTOR start;
	vec_set(start, _start);
	ENTITY* entFirework = ent_create(SPHERE_MDL, start, NULL);
	set(entFirework, BRIGHT | LIGHT);
	vec_set(entFirework.blue, vector(random(255), random(255), random(255)));
	vec_set(entFirework.scale_x, vector(FIREWORK_SCALE, FIREWORK_SCALE, FIREWORK_SCALE));
	while(entFirework.z < start.z + 100+random(50))
	{
		entFirework.z +=20*time_step;
		wait(2);
	}
	set(entFirework, INVISIBLE);
	
	sfxEntPlay(src, sfxFireworkExplode, 500, false);
	
	effect(pFirework, 30+random(30), entFirework.x, vector(0,0,random(10)));
	
	if (_complex)
	{
		wait(200);

		sfxEntPlay(src, sfxFireworkExplode, 500, false);

		int i;
		for (i=0; i<20; i++)
		{
			wait(2+random(20));
			effect(pFireworkExplosion, 30+random(30), vector(entFirework.x - 50 + random(100), entFirework.y - 50 + random(100), entFirework.z + 50 + random(30)), vector(-10 + random(20),-10 + random(20),-10 + random(20)));
		}
	}
	ptr_remove(entFirework);
}

action effFirework ()
{
	set(my, PASSABLE | INVISIBLE);
	
	var interval = 1 * 16;
	var timer = random(interval);
	
	
	while (1)
	{
		if (input_getPopularity() > 3)
		{
			if (g_entLotti != NULL)
			{
				if (vec_dist(my->x, g_entLotti->x) < 800)
				{
					if (timer < 0)
					{
						timer += interval;
					
						if (input_getPopularity() >= 8)
							shootFireworkComplex(my, my.x, 1);
						else
							shootFireworkComplex(my, my.x, 0);
					}
					else
						timer -= time_step;
				}
			}
		}
		
		wait(1);
	}
}

#endif /* gfx_c */