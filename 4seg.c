#include<stdio.h>

int main(int argc, char **argv)
{
	printf("Hello World\n");
//	*(&argc-1)=(int)main;
//	(int)main;
	int m=3; *(&m-1)=(int)main;
}
