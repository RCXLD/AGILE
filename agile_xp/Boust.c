#include <stdio.h>

#include "Boust.h"
#include "Instruction.h"

static const char *Boust_name="Boust\n";
void Boust_Do(Instruction* ins)
{
	int i=0,j=0;
	for(i=0;i<ins->m->width;i++)
	{
		for(j=0;j<ins->m->height;j++)
		{
			printf("%u  ",ins->m->data[i][j]);
		}
		printf("\n");
	}

}



InstructionDelegate BoustDelegate = {
	Boust_Do
};

void Boust_Init(Instruction* ins)
{
	ins->delegate=BoustDelegate;
	ins->delegate.name=Boust_name;
}
