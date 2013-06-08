#include <stdio.h>
int main()
{
int i;
__asm__ volatile("movl %ebp,4(%esp)");
printf("%%ebp=%08x\n");
return 0;
}
