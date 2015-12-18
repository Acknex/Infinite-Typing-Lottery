/*
 *******************************************************************************
 * input.c
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */

#include "typewriter.h"
#include "codeloader.h"

#define CODE_LEVELWAITTIME 48

STRING* strInputTempStr = "@";

STRING* strFullLine;
STRING* strProgressedLine;
STRING* strTypedLine;
STRING* strInputEmptyStr = "\n";
var vAccuracy;
var vLetterPos;
var vLettersTyped;
var vLettersCorrect;
var vInputEnabled;
var vInputFinished;
var vPopularity;
var vLevelTimer;
var vCodeFinishEarly;
SOUND* sndFine;
SOUND* sndFail;
SOUND* sndLevelGood;
SOUND* sndLevelBad;


CODELINE* sLine;
var vInputTime;
var vLetterTime;
var vLevel;
var vFinished;

//local function prototypes
void input_newText();
void input_newLine();
void input_nextLetter();
var input_compare();
void input_finishWord();
void input_finishLevel();


//local functions

void input_newText()
{
	var vError = 0;
	vLevel++;
	vError = code_load(vLevel);

	if (vError != 0)
	{
		vFinished = 1;
		input_disable();
	}
	else
	{
		sLine = code_getNextLine();	
		vLevelTimer = CODE_LEVELWAITTIME;
		if (sLine != NULL)
		{
			input_newLine();
		}
	}
}

void input_newLine()
{
	vInputFinished = 0;
	vInputTime = 0;
	vLetterTime = 0;
	vLetterPos = 0;
	str_cpy(strProgressedLine, "");

	//workaround: don't display new string right after level change
	if (vLevelTimer == 0)
		strFullLine = sLine->strCodeLine;

	typewriter_reset();
	typewriter_setLimit(sLine->vCodeLineLetterCount);
	typewriter_enable();
}

void input_nextLetter()
{
	vLetterTime -= sLine->vCodeLineLetterTime;
	(strInputTempStr->chars)[0] = (sLine->strCodeLine->chars)[vLetterPos];

	str_cat(strProgressedLine, strInputTempStr);

	//advance to next letter
	vLetterPos++;
}


var input_compare()
{
	var x;
	var vErrorCount;
	var vLetterCount;
	
	vErrorCount = 0;
	vLetterCount = str_len(strTypedLine);
	
	for (x = 0; x < vLetterCount; x++)
	{
		//Compare strings letter by letter and count mismatches
		if((strTypedLine->chars)[x] != (strFullLine->chars)[x])
			vErrorCount++;			
	}

	//if typing was not finished count each missing letter as error
	if (vLetterCount < sLine->vCodeLineLetterCount)
		vErrorCount += sLine->vCodeLineLetterCount - vLetterCount;
	
	return vErrorCount;
}

void input_finishWordEarly()
{
	if (strTypedLine != NULL)
	{
		//only accept enter press is string has at least 2 letters
		if (str_len(strTypedLine) >= 2)
		{
			vCodeFinishEarly = 1;
			input_finishWord();
		}
	}
}

void input_finishWord()
{
	var vErrors;
	var vSndHandle;
	
	//check input data
	vErrors = input_compare();
	
	//acoustic feedback
	if (vErrors != 0)
	{
		vSndHandle = snd_play(sndFail, 100, 0);
	}
	else
	{
		vSndHandle = snd_play(sndFine, 100, 0);
	}

	snd_tune(vSndHandle, 0, random(60) + 70, 0);

	//rating
	vLettersTyped   += sLine->vCodeLineLetterCount;
	vLettersCorrect += sLine->vCodeLineLetterCount - vErrors;
	vAccuracy = 100 * vLettersCorrect / vLettersTyped;
	
	vInputFinished = 1;
	typewriter_reset();
	typewriter_disable();
}

void input_finishLevel()
{
	if (vAccuracy > 80)
	{
		snd_play(sndLevelGood, 100, 0);
		vPopularity++;
	}
	else
	{
		snd_play(sndLevelBad, 50, 0);
		vPopularity--;
	}
	
	vPopularity = clamp(vPopularity, 1, 10);
}


//global functions
void input_init()
{
	//init codeloader
	code_init();
	//init typewriter
	typewriter_init();

	vInputTime = 0;
	vLetterTime = 0;
	vLevel = 0;
	vLetterPos = 0;
	vAccuracy = 100;
	vPopularity = 1;
	vFinished = 0;
	vLettersTyped = 0;
	vLettersCorrect = 0;
	vInputEnabled = 0;
	vInputFinished = 0;
	vLevelTimer = 0;
	vCodeFinishEarly = 0;
	sndFine      = snd_create("juhu.ogg");
	sndFail      = snd_create("aiaiaiai.ogg");
	sndLevelGood = snd_create("crowdCheer0.ogg");
	sndLevelBad  = snd_create("fail.wav");

	strProgressedLine = str_create("");
	input_newText();
}

void input_loop()
{
	//wait between level change
	if (vLevelTimer > 0)
	{
		vLevelTimer = maxv(0, vLevelTimer - time_step);
		if (vLevelTimer == 0)
		{
			strFullLine = sLine->strCodeLine;
			typewriter_enable();
		}
		else
		{
			strFullLine = strInputEmptyStr; //avoid empty pointer crash - not nice, but I'm running out of time
			typewriter_disable();
		}
	}
	else
	{		
		strTypedLine = typewriter_getString();
		if ((sLine != NULL) && (vFinished == 0) && (vInputEnabled == 1))
		{
			vInputTime  += time_step;
			vLetterTime += time_step;
		
			if ((vLetterTime >= sLine->vCodeLineLetterTime) && (vLetterPos < sLine->vCodeLineLetterCount))
			{
				input_nextLetter();
			}
		
			if ((vInputTime >= sLine->vCodeLineMaxTime) || (vCodeFinishEarly != 0))
			{
				if (vInputFinished == 0)
					input_finishWord();
					
				vCodeFinishEarly = 0;
				sLine = code_getNextLine();
		
				//last line found - get new file
				if (sLine == NULL)
				{
					input_finishLevel();
					input_newText();
				}
				//next line found
				else
				{	
					input_newLine();
				}
			}
			
		}
	}
}

var input_getLevel()
{
	return vLevel;
}

var input_getFinished()
{
	return vFinished;
}

var input_getAccuracy()
{
	return vAccuracy;
}

var input_getLetterCount()
{
	return vLettersTyped;
}

var input_getErrorCount()
{
	return vLettersTyped - vLettersCorrect;
}

var input_getPopularity()
{
	return vPopularity; 
}


void input_enable()
{
	vInputEnabled = 1;
	on_enter = input_finishWordEarly;
	typewriter_enable();
}

void input_disable()
{
	vInputEnabled = 0;
	on_enter = NULL;
	typewriter_disable();
	strFullLine = strInputEmptyStr;
	strTypedLine = strInputEmptyStr;
 	str_cpy(strProgressedLine, "");
}
