#pragma once

#ifndef LY_MATRIX_H
#define LY_MATRIX_H

#include <stdio.h>


typedef struct
{
	unsigned int width;
	unsigned int height;
	unsigned int **data;
}Matrix;


extern void Matrix_init(Matrix* self,unsigned int w,unsigned int h);
extern void Matrix_destroy(Matrix* self);

extern void Matrix_get(Matrix* self, unsigned int i,unsigned int j);
extern void Matrix_set(Matrix* self, unsigned int i,unsigned int j,unsigned int value);

#endif /*LY_MATRIX_H*/
