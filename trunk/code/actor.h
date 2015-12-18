#ifndef actor_h
#define actor_h

#define ACTOR_WALK_SPEED skill1
#define ACTOR_WALK_FAC skill2

#define ACTOR_WALK_ANIM_SPEED skill3
#define ACTOR_IDLE_ANIM_SPEED skill4

#define ACTOR_WALK_SFX_TIMER skill5
#define ACTOR_WALK_SFX_THRESH skill6
#define ACTOR_WALK_SFX_INDEX skill7

var g_actorAmbient = 150;

void assertMipMaps (ENTITY* ent);

void actorInit (ENTITY* ent);

void actorSetShadow (ENTITY* ent, BOOL noSelfShadow);
var actorAttachNextPath (ENTITY* ent, char* pathname);

void actorWalkPath (ENTITY* ent);
void actorWalkPath (ENTITY* ent, BOOL randomPathPos);
void actorWalkPath (ENTITY* ent, char* pathname, BOOL randomPathPos);

#include "actor.c"

#endif /* actor_h */