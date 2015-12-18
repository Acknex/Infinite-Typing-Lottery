#ifndef sky_c
#define sky_c

#include "sky.h"

void skychange ()
{
	COLOR oldColor, newColor;
	var factor = 0.0;
	
	vec_set(oldColor.blue, screen_color.blue);
	vec_set(newColor.blue, vector(random(255), random(255), random(255)));
	
	while (1)
	{
		factor += 0.2 * time_step;
		factor = clamp(factor, 0.0, 1.0);
		
		vec_lerp(screen_color.blue, oldColor.blue, newColor.blue, factor);
		vec_set(sky_color.blue, screen_color.blue);
		
		if (factor == 1.0)
		{
			factor = 0.0;
			vec_set(oldColor.blue, screen_color.blue);
			vec_set(newColor.blue, vector(random(255), random(255), random(255)) );
		}	
		
		wait(1);
	}
}

#endif /* sky_c */