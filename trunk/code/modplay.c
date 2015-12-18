/////////////////////////////////////////////////////////////////////////
// Wrapper for bass.dll - Version 1.0 (03/31/02) update 06/16/12	   //
// created by Firoball - http://www.firoball.de - robert@firoball.de   //
/////////////////////////////////////////////////////////////////////////

#include <acknex.h>
#include "basswrap.h"

var mod_handle;
//STRING* MOD_Filename = "muffler_pissi.xm";
STRING* MOD_Filename = "music\\mMain.ogg";
float fft[1024];


void music_start()
{
	mod_init(MOD_HIGHFREQ,MOD_INIT3D);
//	mod_volume(50);
	mod_handle=mod_load(MOD_Filename,MOD_LOADLOOP+MOD_LOADSURROUND);
	mod_play(mod_handle);
//	mod_amplify(mod_handle, 2);
}

void music_stop()
{
	mod_stop(mod_handle);
}

var music_processChannel()
{
	var x;
	float medium = 0;
	mod_getdata(mod_handle, fft, BASS_DATA_FFT2048);
	
	for(x = 0; x < 256; x++)
	{
		medium += fft[x];
	}
	medium /= 256.0;
	
	return medium * 10000;
}
