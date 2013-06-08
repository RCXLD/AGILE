#pragma once

#ifndef SCANLINE_H
#define SCANLINE_H

#include "Instruction.h"

typedef struct 
{
	int a;
}Scanline;


extern void Scanline_Do(Instruction* ins);
extern void Scanline_Init(Instruction* ins);



#endif /*SCANLINE_H*/
