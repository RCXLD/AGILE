#pragma once

#ifndef LY_INSTRUCTION_H
#define LY_INSTRUCTION_H

#include <stdio.h>

#include "Matrix.h"

struct i_Instruction;

#pragma once
typedef struct 
{
/*Destroy Stack*/
void (*Do)(struct i_Instruction* ins);
char* name;
}InstructionDelegate;


struct i_Instruction
{
void *data;		//For future , we could add something more.
Matrix *m;		
InstructionDelegate delegate;
};

typedef struct i_Instruction Instruction;

extern void Instruction_Destroy(Instruction* ins);
extern void Instruction_Init(Instruction *ins,Matrix *s);

extern void Instruction_Getname(Instruction* ins);
extern void Instruction_Do(Instruction* ins);
#endif /*LY_INSTRUCTION_H*/


