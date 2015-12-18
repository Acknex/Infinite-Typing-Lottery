#ifndef _CREDITS_C_
#define _CREDITS_C_

#include <acknex.h>
#include <windows.h>
#include "input.h"

TEXT *txtCredits;
FONT *fontCredits;

function credits_flyparts_event(PARTICLE *p)
{
	p->alpha -= 50 * time_step;
	if(p->alpha < 0)
		p->lifespan = 0;
}

function credits_flyparts(PARTICLE *p)
{
	p.vel_z = 50;
	set(p, TRANSLUCENT | MOVE | STREAK | BRIGHT);
	p->alpha = 5;
	p->event = credits_flyparts_event;
}

function credits_flyparts2(PARTICLE *p)
{
	p.vel_z = 50;
	set(p, TRANSLUCENT | MOVE | BRIGHT);
	p->alpha = 50;
	p->lifespan = 4;
	p->event = credits_flyparts_event;
}

function credits_overkill()
{
	my.ambient = -100;
	set(me, LIGHT);
	while(1)
	{
		wait(-10 - random(10));
		
		var time = 32;
		while(time > 0)
		{
			my.red = cycle(my.red + 15 * time_step, 0, 256);
			my.green = cycle(my.green + 25 * time_step, 0, 256);
			my.blue = cycle(my.blue - 35 * time_step, 0, 256);
			time -= time_step;
			wait(1);
		}
		vec_fill(my.blue, 255);
		
		wait(1);
	}
}

int creditsCurrentItem = 0;
STRING *strCurrentLyricLine = "#256";
STRING *strNextLyricLine = "#256";
TEXT *txtLyrics;

var lyrics_next()
{
	STRING *strTemp = "#256";
	str_cpy(strNextLyricLine, (txtLyrics->pstring)[creditsCurrentItem]);
	creditsCurrentItem++;
	str_cpy(strTemp, strNextLyricLine);
	int offset = str_chr(strNextLyricLine, 1, ' ');
	
	str_trunc(strTemp, offset);
	var time = str_to_num(strTemp);
	
	str_clip(strNextLyricLine, offset);
	
	// return time in milliseconds
	return 1000 * time;
}

DWORD GetTickCount(void);

function credits_init()
{	
	while(!input_getFinished()) wait(1);
	wait(2);
	
	input_disable();
	reset(pnlBgPanel, SHOW);
	music_stop();
	
	wait(-4);
	
	snd_play(sndLevelFinished, 100, 0);
	
	wait(-6);
	
	level_load(NULL);
	
	camera->arc = 65;
	
	g_hdrThreshold = 40;
	g_hdrStrength = 20;	
	
	fontCredits = font_create("Arial#32");
	txtCredits = txt_create(1000, 5);
	txtCredits.font = fontCredits;
	txt_load(txtCredits, "world\\credits.txt");
	txtCredits.flags |= CENTER_X | SHOW | OUTLINE;
	txtCredits.pos_y = screen_size.y;
	set(txtCredits, LIGHT);
	var yoffset = 0;
	
	vec_set(txtCredits.blue, vector(random(256),random(256),255));
	
	var timeSwitch = 32;
	
	ENTITY* entLotti = ent_create("cLotter.mdl", vector(128, 0, -24), credits_overkill);
	entLotti.pan = 180;
	
	var lottiAnim = 0;
	
	var i = 0;
	
	var media = media_play("music\\mRhapsody.ogg", NULL, 100);
	midi_vol = 100;
	
	ENTITY* entBackground = ent_create("background.mdl", vector(0, 0, 0), NULL);
	
	txtLyrics = txt_create(100, -1);
	txt_load(txtLyrics, "world\\lyrics.txt");
	
	var nextLyrics = lyrics_next();
	var timeLyrics = 0;
	
	TEXT *txtLyricLine = txt_create(1, 10);
	txtLyricLine->font = font_create("Courier#16");
	txtLyricLine->flags |= CENTER_X | SHOW;
	(txtLyricLine->pstring)[0] = strCurrentLyricLine;
	
	PANEL *panLyricBackground = pan_create("", 9);
	panLyricBackground->flags |= LIGHT | SHOW;
	panLyricBackground->size_x = 500;
	panLyricBackground->size_y = 32;
	vec_set(panLyricBackground->blue, vector(128, 128, 128));
	
	HMODULE mod = LoadLibrary("Kernel32.dll");
	GetTickCount = GetProcAddress(mod, "GetTickCount");
	
	DWORD startupTime = GetTickCount();
	
	PANEL *censored = pan_create("", 4);
	censored.size_x = 90;
	censored.size_y = 30;
	censored.bmap = bmap_create("censored.png");

	while(1)
	{
		txtCredits.pos_x = screen_size.x / 2;
		txtCredits.pos_y = screen_size.y - yoffset;	
		
		txtLyricLine.pos_x = screen_size.x / 2;
		txtLyricLine.pos_y = 8;
		
		panLyricBackground.size_x = screen_size.x;
		
		VECTOR pos;
		vec_set(pos, entLotti.x);
		vec_to_screen(pos, camera);
		
		censored.pos_x = pos.x - 45;
		censored.pos_y = pos.y - 10;
		
		if(abs(ang(entLotti.pan)) < 30)
			set(censored, SHOW);
		else
			reset(censored, SHOW);
		
		if(timeSwitch <= 0)
		{
			vec_set(txtCredits.blue, vector(random(256),random(256),255));
			timeSwitch = 32;
		}
		
		var iSpecial = integer(random(ent_status(entLotti, 0)) + 1);
		for(i = 0; i < ent_status(entLotti, 0); i += 10)
		{
			VECTOR pos;
			vec_for_vertex(pos, entLotti, i + 1);
			effect(credits_flyparts, 1, pos, nullvector);
			if(i == iSpecial)
				effect(credits_flyparts2, 1, pos, nullvector);
		}
		
		ent_animate(entLotti, "fly", lottiAnim, ANM_CYCLE);
		
		entBackground.v -= 75 * time_step;
		
		entLotti.pan += time_step;
		yoffset += 1.2 * time_step;
		timeSwitch -= time_step;
		lottiAnim += 5 * time_step;
		
		if(nextLyrics <= GetTickCount() - startupTime)
		{
			str_cpy(strCurrentLyricLine, strNextLyricLine);
			if(str_cmpni(strCurrentLyricLine, "EXIT_GAME"))
			{
				sys_exit(NULL);
			}
			nextLyrics = lyrics_next();
		}
		
		wait(1);
	}
}

#endif // #ifndef _CREDITS_C_