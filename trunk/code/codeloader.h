/*
 *******************************************************************************
 * codeloader.h
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */

#ifndef CODELOADER_H
#define CODELOADER_H

typedef struct
{
	STRING* strCodeLine;
	var vCodeLineMaxTime;
	var vCodeLineLetterTime;
	var vCodeLineLetterCount;
}CODELINE;


void code_init();
var code_load(var vNum);
CODELINE* code_getNextLine();

#include "codeloader.c"

#endif