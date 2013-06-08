#include <stdio.h>

#include "Scanline.h"
#include "Instruction.h"

static const char *Scanline_name="Scanline\n";
void Scanline_Do(Instruction* ins)
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



InstructionDelegate ScanlineDelegate = {
	Scanline_Do
};

void Scanline_Init(Instruction* ins)
{
	ins->delegate=ScanlineDelegate;
	ins->delegate.name=Scanline_name;
}
