#include <stdio.h>
/*
int add(int x,int y)
{
	return x+y;
}
*/
char a[]={'\x55', '\x89' ,'\xe5' ,'\x8b' ,'\x55' ,'\x0c' ,'\x8b', '\x45' ,'\x08' ,'\x01' , '\xd0', '\x5d', '\xc3'};

int main()
{
	printf("add=%d\n",((int(*) (int,int))a)(3,4));
	return 0;
}
