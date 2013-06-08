#include <stdio.h>

#include "Matrix.h"
#include "Scanline.h"
#include "Instruction.h"


void main()
{
	Matrix *mx;
	Matrix_init(&mx,4,3);
	Matrix_set(&mx,1,1,2);

	Scanline *s;
	Instruction ist;


	Instruction_Init(&ist,&mx);
	Scanline_Init(&ist);
	Instruction_Do(&ist);
	Instruction_Getname(&ist);


	Instruction_Destroy(&ist);






}
