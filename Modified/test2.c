#include <stdio.h>
#include <nids.h>

void ip_frag_func(struct ip * a_packet)
{
	static int count = 0;
	printf("ip_frag_func called (%d)\n",count++);
}

void ip_func(struct ip * a_packet)
{
	static int count = 0;
	printf("ip_Func called (%d)\n",count++);
}

int main()
{
	nids_init();
	nids_register_ip_frag(ip_frag_func);
	nids_register_ip(ip_func);
	nids_run();
	//never reached
	printf("Terminated.\n");
	return 0;
}
