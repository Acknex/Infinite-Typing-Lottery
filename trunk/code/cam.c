#ifndef cam_c
#define cam_c

#include "cam.h"

VECTOR* ang_lerp (VECTOR* resultVec, VECTOR* srcVec, VECTOR* destVec, var blendFactor)
{
	VECTOR ANG_LERP_VEC;

	vec_set(resultVec, srcVec);						// Copy source into result
	vec_diff(ANG_LERP_VEC, destVec, resultVec);  // Difference vector

	ANG_LERP_VEC.x = ang(ANG_LERP_VEC.x);			// Adjust angle validity
	ANG_LERP_VEC.y = ang(ANG_LERP_VEC.y);
	ANG_LERP_VEC.z = ang(ANG_LERP_VEC.z);

	vec_scale(ANG_LERP_VEC.x, blendFactor);		// Interpolate the rotation
	vec_add(resultVec, ANG_LERP_VEC);				// Apply interpolated angle

	return(resultVec);									// Return result angle
}

void vec_acc (VECTOR* from, var pr, VECTOR* to)
{
	to->x += from->x * pr;
	to->y += from->y * pr;
	to->z += from->z * pr;
}

void accCam (VECTOR* vPos, VECTOR* vAng, var* sArc, var fac, VECTOR* accPos, VECTOR* accAng, var* accArc, var* accPr)
{
	vec_acc(vPos, fac, accPos);
	vec_acc(vAng, fac, accAng);
	*accArc += fac * *sArc;
	*accPr += fac;
}

void updateCam (ENTITY* ent, int* camType)
{
	var sArc;
	VECTOR vPos, vAng;
	
	camInterval = (4 + ((11 - input_getPopularity()) / 11) * 10) * 16;
	
	if (camTimer < 0)
	{
		camTimer += camInterval;
		*camType = (*camType + 1) % CAM_TYPES;
	}
	else
		camTimer -= time_step;
	
	switch (*camType)
	{	
		case CAM_TYPE_FOLLOW:
			getCamFollow(ent, &vPos, &vAng, &sArc);
			break;
			
		case CAM_TYPE_FACE:
			getCamFace(ent, &vPos, &vAng, &sArc);
			break;
			
		case CAM_TYPE_BIRD:
			getCamBird(ent, &vPos, &vAng, &sArc);
			break;		

		case CAM_TYPE_SIDE:
			getCamSide(ent, &vPos, &vAng, &sArc);
			break;
			
		case CAM_TYPE_ISO:
			getCamIso(ent, &vPos, &vAng, &sArc);
			break;
			
		case CAM_TYPE_CYLINDER:
			getCamCylinder(ent, &vPos, &vAng, &sArc);
			break;					
	}
	
	vec_lerp(camera->x, camera->x, &vPos, 0.3 * time_step);
	ang_lerp(camera->pan, camera->pan, &vAng, 0.3 * time_step);
	
	camera->arc = sArc;
	
	VECTOR from;			
	vec_set(&from, camera->x);
	from.z += 1000;
	
	VECTOR to;
	vec_set(&to, camera->x);
	to.z -= 9999;
	
	var mode = (IGNORE_PASSABLE | IGNORE_SPRITES);
	var d = c_trace(&from, &to, mode);	
	if (d > 0)
	{
		var minDist = 32;
		
		if (vec_dist(camera->x, hit->x) < minDist)
			camera->z += minDist - vec_dist(camera->x, hit->x);
	}
}

void getCamFollow (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 60 + ent->ACTOR_WALK_FAC * 15;

	VECTOR v;
	
	vec_set(&v, vector(-300, 0, 25 + ent->ACTOR_WALK_FAC * 25));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	vec_diff(&v, ent->x, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = 0; // roll
}

void getCamFace (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 40;

	VECTOR v;
	
	vec_set(&v, vector(120, 0, 20));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	//vec_lerp(camPos, camera->x, &v, 0.75 * time_step);
	
	VECTOR p;
	vec_set(&p, vector(0,0,15));
	vec_rotate(&p, ent->pan);
	vec_add(&p, ent->x);
	
	vec_diff(&v, &p, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = 0; // roll
}

void getCamBird (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 90;

	VECTOR v;
	
	vec_set(&v, vector(-10, 0, 300));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	VECTOR p;
	vec_set(&p, vector(30,0,0));
	vec_rotate(&p, ent->pan);
	vec_add(&p, ent->x);
	
	vec_diff(&v, &p, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = total_ticks % 360;
}

void getCamSide (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 70;

	VECTOR v;
	
	vec_set(&v, vector(0, 300, 50));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	VECTOR p;
	vec_set(&p, vector(10,0,10));
	vec_rotate(&p, ent->pan);
	vec_add(&p, ent->x);
	
	vec_diff(&v, &p, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = -((total_ticks * 2) % 360);
}

void getCamIso (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 20;

	VECTOR v;
	
	vec_set(&v, vector(1000, -1000, 1000));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	vec_diff(&v, ent->x, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = 0;
}

void getCamCylinder (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc)
{
	*camArc = 90;

	VECTOR v;
	
	vec_set(&v, vector(100, 0, 0));
	vec_rotate(&v, vector(total_ticks * 8, 0, 0));
	vec_rotate(&v, ent->pan);
	vec_add(&v, ent->x);
	
	vec_set(camPos, &v);
	
	vec_diff(&v, ent->x, camPos);
	vec_to_angle(camAng, &v);
	
	camAng->z = 0;
}

#endif /* cam_c */