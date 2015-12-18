/*
 *******************************************************************************
 * codeloader.c
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */

#include <strio.c>

#define CODE_LETTERTIME 10

void code_strClean(STRING* strData);

CODELINE sCodeline;
TEXT* txtCode;
var vCodeLines;
var vCodeCurrentLine;
var vCodeError;
var vCodeNumber;
var vDisplaySpeed;
STRING* strCodeCurrentLine;


void code_init()
{
	vCodeLines = 0;
	vCodeCurrentLine = 0;
	vCodeError = 0;
	txtCode = txt_create(10000,0);
	str_cpy(delimit_str, "ä"); //get rid of comma separator
	strCodeCurrentLine = str_create("");
	vDisplaySpeed = 0.8;

	sCodeline.strCodeLine = str_create("");
	sCodeline.vCodeLineMaxTime = 0;
	sCodeline.vCodeLineLetterTime = 0;
	sCodeline.vCodeLineLetterCount = 0;
}

var code_load(var vNum)
{
	STRING* strFile = str_printf(NULL, "listings\\code%d.txt", (int)vNum);

	if (file_open_read(strFile))
	{
		vCodeLines = txt_load(txtCode, strFile);
		vCodeNumber = vNum;
		vCodeError = 0;
		vCodeCurrentLine = 0;
		vDisplaySpeed += 0.1;
	}
	else
	{
//		error("File not found!");	
		vCodeError = 1;
	}

	return vCodeError;
}

CODELINE* code_getNextLine()
{
	var vFound = 0;
	
	if ((vCodeCurrentLine < vCodeLines) && (vCodeError == 0))
	{
		do
		{
			str_cpy(strCodeCurrentLine, (txtCode->pstring)[vCodeCurrentLine]);
			code_strClean(strCodeCurrentLine);
			vCodeCurrentLine++;
			if (str_len(strCodeCurrentLine) > 1)
			{
				vFound = 1;
			}
		} while ((vCodeCurrentLine < vCodeLines) && (vFound == 0));

		if (vFound != 0)
		{
			str_cpy(sCodeline.strCodeLine, strCodeCurrentLine);
			sCodeline.vCodeLineLetterCount = str_len(strCodeCurrentLine);
			sCodeline.vCodeLineLetterTime  = CODE_LETTERTIME / vDisplaySpeed;
			sCodeline.vCodeLineMaxTime     = sCodeline.vCodeLineLetterTime * sCodeline.vCodeLineLetterCount + sCodeline.vCodeLineLetterTime;

			return &sCodeline;			
		}
		else
			return NULL; //last line reached
	}
	else
	{
		return NULL; //last line reached or problem with loaded code
	}
}

void code_strClean(STRING* strData)
{
	var l = 0;

	/* kill tabs */
	str_replaceall(strData, "	", " ");

	/* kill leading spaces */
	do
	{
		l = str_stri(strData, " ");
		if (l == 1)
			str_clip(strData, 1);
	}while (l == 1);
	
	/* kill trailing spaces */
	do
	{
		l = str_getchr(strData, str_len(strData));
		if (l == ' ')
			str_trunc(strData, 1);
	}while (l == ' ');
}
