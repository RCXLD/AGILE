#include <nids.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void load(void *data, int len)
{
	int i;
	for(i = 0; i < 100000; i ++)
	{    
	    i = i % 9999999 ;
	}

}

void cnter(void *data, int len)
{
	static int cnt = 0;
	static clock_t t = 0;
	if(!t)
		t = - time(NULL);
	cnt ++;
	if(cnt > 10000)
	{
		t += time(NULL);
		printf("time = %ld\n", t);
		nids_exit();
		exit(0);
	}
	else
		/*printf("cnt = %d\n",cnt);*/
	    ;
}

int main()
{
	if(!nids_init())
		puts("fail to init.");
	nids_register_ip_frag(load);
	nids_register_ip(cnter);

	nids_run();
}
