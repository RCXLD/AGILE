#pragma once

#ifndef BOUST_H
#define BOUST_H

#include "Instruction.h"

typedef struct 
{
	int a;
}Boust;


extern void Boust_Do(Instruction* ins);
extern void Boust_Init(Instruction* ins);



#endif /*Boust_H*/
