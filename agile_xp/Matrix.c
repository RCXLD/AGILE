#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "Matrix.h"



void Matrix_init(Matrix* self,unsigned int w,unsigned int h)
{
	int i=0,j=0;
	self->height=h;
	self->width=w;

	self->data=(unsigned int *)malloc(sizeof(unsigned int)*(w));
	
	for(i=0;i<w;i++)
	{
		self->data[i]=(unsigned int *)malloc(sizeof(unsigned int)*(h));
	}

	for(i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
			self->data[i][j]=0;
		}
	}

}

void Matrix_destroy(Matrix* self)
{
	int i=0;
	for(i=0;i<self->width;i++)
	{
		free(self->data[i]);
	}
	free(self->data);
}

unsigned int Matrix_get(Matrix* self, unsigned int i,unsigned int j)
{
	return self->data[i][j];

}

void Matrix_set(Matrix* self, unsigned int i,unsigned int j,unsigned int value)
{
	self->data[i][j]=value;
}