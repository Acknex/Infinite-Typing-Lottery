#ifndef hdr_c
#define hdr_c

#include <mtlView.c>
#include "hdr.h"

void hdr ()
{
	pp_set(camera, mtl_hdr);
	
	while (1)
	{
		mtl_hdr.skill1 = floatv(g_hdrStrength);
		mtl_hdr.skill2 = floatv(g_hdrThreshold);
		
		wait(1);
	}
}

#endif /* hdr_c */