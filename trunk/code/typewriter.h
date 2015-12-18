/*
 *******************************************************************************
 * typewriter.h
 * Creation date: 16.06.2012
 * Author:        Firoball
 *
 *******************************************************************************
 */

#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <acknex.h>

void typewriter_enable();
void typewriter_disable();
void typewriter_reset();
STRING* typewriter_getString();
void typewriter_setLimit(var vLimit);

#include "typewriter.c"

#endif