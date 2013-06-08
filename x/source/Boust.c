#include <stdio.h>

#include "Boust.h"
#include "Instruction.h"

static const char *Boust_name="Boust\n";
void Boust_Do(Instruction* ins)
{
	int i=0,j=0;
	for(i=0;i<ins->m->width;i++)
	{
		j=0;
		if(i%2==1)
		{
		if(j>=ins->m->height)
		{break;}			
			printf("%u  ",ins->m->data[i][j]);
			j++;
		}
		
		else
		{
		if(j<0)
		{break;}
		
		j=m->height-1;

		printf("%u  ",ins->m->data[i][j]);
		j--

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
