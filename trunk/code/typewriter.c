/*
 *******************************************************************************
 * typewriter.c
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */
#include <windows.h>

var vTypewriterEnabled;
var vTypewriterTextLength;
STRING* strTypewriter;
STRING* strMessage = " ";
SOUND* sndTypewriter;
SOUND* sndDeleteLetter;
SOUND* sndTypeWriterLetter[26];

LRESULT CALLBACK AcknexMsgLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK typewriter_msgLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK typewriter_msgLoop(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char c = (char)wParam;
	var vSndHandle;
	
	if (message == WM_CHAR)
   {
		if (
				(c > 31) && (c < 127) && (vTypewriterEnabled != 0) && //ignore special codes
				(str_len(strTypewriter) < vTypewriterTextLength)
			) 	
		{
			(strMessage->chars)[0] = c;
			str_cat(strTypewriter, strMessage);
			
			//check if letter was typed
			if ((c >= 65) && (c <= 90))
			{
				vSndHandle = snd_play(sndTypeWriterLetter[c-65], 100, 0);
			}
			else if ((c >= 97) && (c <= 122))
			{
				vSndHandle = snd_play(sndTypeWriterLetter[c-97], 100, 0);
			}
			else
			{
				vSndHandle = snd_play(sndTypewriter, 30, 0);
				snd_tune(vSndHandle, 0, random(60)+70, 0);
			}
   	}

		//backspace handling
		else if (c == 8)
		{
			if (str_len(strTypewriter) > 0)
			{
				str_trunc(strTypewriter, 1);
				vSndHandle = snd_play(sndDeleteLetter, 100, 0);
				snd_tune(vSndHandle, 0, random(60)+70, 0);
			}
		}
   }

	//engine message loop
   return AcknexMsgLoop(hwnd, message, wParam, lParam);       
}

void typewriter_init()
{
	var x;
	STRING* strTemp = str_create("N.ogg");
	
	vTypewriterEnabled = 0;
	vTypewriterTextLength = 0;
	strTypewriter = str_create("");
	AcknexMsgLoop = on_message;
	on_message = typewriter_msgLoop;
	sndTypewriter = snd_create("type.ogg");
	sndDeleteLetter = snd_create("oops.ogg");

	for (x = 0; x < 26; x++)
	{
		(strTemp->chars)[0] = (char)((int)x + 65); //get letter for sound name
		sndTypeWriterLetter[x] = snd_create(strTemp);
	}

	ptr_remove(strTemp);

}

void typewriter_enable()
{
	vTypewriterEnabled = 1;
}

void typewriter_disable()
{
	vTypewriterEnabled = 0;
}

void typewriter_reset()
{
	//clear typewriter string
	str_cpy(strTypewriter, "");
}

STRING* typewriter_getString()
{
	return strTypewriter;
}

void typewriter_setLimit(var vLimit)
{
	vTypewriterTextLength = vLimit;
}


