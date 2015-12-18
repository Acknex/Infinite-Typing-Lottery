/////////////////////////////////////////////////////////////////////////
// Wrapper for bass.dll - Version 1.0 (03/31/02) update 06/16/12	     //
// created by Firoball - http://www.firoball.de - robert@firoball.de   //
/////////////////////////////////////////////////////////////////////////

var mod_load(var x,var y);
var mod_init(var x,var y);
var mod_unload();
var mod_play(var x);
var mod_stop(var x);
var mod_volume(var x);
var mod_getname(var x,var y);
var mod_amplify(var x,var y);
var mod_pause(var x);
var mod_resume(var x);
var mod_getattrib(var x, var y);
var mod_getdata(var x, float* b, long y);
var mod_volume(var x);

//Attributes
#define BASS_MUSIC_ATTRIB_AMPLIFY	0
#define BASS_MUSIC_ATTRIB_PANSEP	1
#define BASS_MUSIC_ATTRIB_PSCALER	2
#define BASS_MUSIC_ATTRIB_BPM		3
#define BASS_MUSIC_ATTRIB_SPEED		4
#define BASS_MUSIC_ATTRIB_VOL_GLOBAL 5
#define BASS_MUSIC_ATTRIB_VOL_CHAN	0x100 // + channel #
#define BASS_MUSIC_ATTRIB_VOL_INST	0x200 // + instrument # 

//Frequency Options
#define MOD_LOWFREQ		11025
#define MOD_MEDFREQ		22050
#define MOD_HIGHFREQ	44100 //default;


//Quality Flags (default: all turned off)
#define MOD_INIT8BIT	1	//8Bit playback for slow systems
#define MOD_INITMONO	2	//Mono playback for even slower systems
#define MOD_INIT3D		4	//3D playback for faster system
#define MOD_INITNOSYNC	8 	//turn this flag on to spare cpu time,
 							//but some mods won't work

//MOD Playback Flags (default: all turned off)
#define MOD_LOADLOOP	4		//Loop MOD until stopped
#define MOD_LOADSURROUND 512	//Enable Surround

// BASS_ChannelGetData flags

#define BASS_DATA_AVAILABLE	0			// query how much data is buffered

#define BASS_DATA_FLOAT		0x40000000	// flag: return floating-point sample data

#define BASS_DATA_FFT512	0x80000000	// 512 sample FFT

#define BASS_DATA_FFT1024	0x80000001	// 1024 FFT

#define BASS_DATA_FFT2048	0x80000002	// 2048 FFT

#define BASS_DATA_FFT4096	0x80000003	// 4096 FFT

#define BASS_DATA_FFT8192	0x80000004	// 8192 FFT
#define BASS_DATA_FFT_INDIVIDUAL 0x10	// FFT flag: FFT for each channel, else all combined

#define BASS_DATA_FFT_NOWINDOW	0x20	// FFT flag: no Hanning window 
