#ifndef shader_c
#define shader_c

#include "shader.h"
#include "game.h"

action acWater ()
{
	my->material = mtlWater;
	my->skill42 = floatv(2);
	
	var t = 0;
	var bass;
	while (1)
	{
		bass = maxv(g_bass-15, 0);
		
		if (bass > 3.0)
		{
			t = 0.0;
		}		
		
		my.skill41 = floatv(t);
		my.skill43 = floatv(100.0+bass);
		t += time_step*0.5;			
		
		my->skill43 = floatv(100+g_bass);
		wait(1);
	}
}

#endif /* shader_c */