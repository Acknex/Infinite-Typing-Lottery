#include <acknex.h>
//#include <default.c>

#define PRAGMA_PATH "code"

#define DO_ENABLE_HDR

#include "system.h"
#include "start.h"
#include "npc.h"
#include "terrain.h"
#include "shader.h"
#include "seedX.h"
#include "rainbow.h"

#include "modplay.h"

#include "typewriter.h"

#include "credits.h"

void stoppspiel ()
{
	music_stop();
	sys_exit("");
}


void main ()
{
	on_esc = stoppspiel;
	
	setSystem();
	credits_init();
	
	wait(3);
	
	openStart();
}