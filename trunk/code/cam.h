#ifndef cam_h
#define cam_h

#define CAM_TYPE_FOLLOW 0
#define CAM_TYPE_FACE 1
#define CAM_TYPE_BIRD 2
#define CAM_TYPE_SIDE 3
#define CAM_TYPE_ISO 4
#define CAM_TYPE_CYLINDER 5

int CAM_TYPES = 6;

int g_camType = 0;

var camTimer = 0;
var camInterval = 10;

void updateCam (ENTITY* ent, int* camType);

void getCamFollow (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);
void getCamFace (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);
void getCamBird (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);
void getCamSide (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);
void getCamIso (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);
void getCamCylinder (ENTITY* ent, VECTOR* camPos, VECTOR* camAng, var* camArc);

#include "cam.c"

#endif /* cam_h */