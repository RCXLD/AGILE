#include <stdio.h>

#include "Instruction.h"

void Instruction_Destroy(Instruction* ins)
{
	ins->data=NULL;
	ins->m=NULL;
}

void Instruction_Init(Instruction *ins,Matrix *x)
{
	ins->data=NULL;
	ins->m=x;
}


void Instruction_Getname(Instruction* ins)
{
	printf("%s",ins->delegate.name);
}
void Instruction_Do(Instruction* ins)
{
ins->delegate.Do(ins);
}
