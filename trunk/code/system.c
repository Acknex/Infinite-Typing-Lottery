#ifndef system_c
#define system_c

#include <mtlView.c>

#include "system.h"

#include "hdr.h"

void setSystem ()
{
	randomize();

	preload_mode = g_preloadMode;
	
	video_screen = 1;
	video_window(NULL, NULL, 0, "Infinite Typing Lottery");
	
	mip_levels = 6;
		
	video_mode = g_videoMode;
	
	camera->clip_near = 1;
	camera->clip_far = 10000;
	
	vec_set(d3d_lodfactor,vector(5,10,20));
	
	#ifdef DO_ENABLE_HDR
		hdr();
	#endif
}

#endif /* system_c */