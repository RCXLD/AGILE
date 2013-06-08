#include <stdio.h>
#include <nids.h>

void load(void *data, int len)
{
    int i;
    for(i = 0; i<100000; i ++)
	i = i % 10000000;
}

void cnter(void *data, int len)
{
    static unsigned t = 0;
    static int cnt = 0;
    if(t == 0)
	t = - clock();
    else
    {
	cnt++;
	if(cnt > 100)
	{
	    t += clock();
	    printf("time = %u\n",t);
	}
    }
}

int main()
{
    if(!nids_init())
	puts("init failure.");
    nids_register_ip_frag(load);
    nids_register_ip(cnter);
    nids_run();
    
}
