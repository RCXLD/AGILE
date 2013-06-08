#include <stdio.h>
#include <stdlib.h>
#include <nids.h>
#include <unistd.h>
#define __USE_GNU
#include <pthread.h>

void msg_print(void *data,int len)
{
  pid_t pid = 0;
  unsigned i, t;
  //puts("call_back called.");
  cpu_set_t mask;
  CPU_ZERO(&mask);
  sched_getaffinity(pid,sizeof(mask),&mask);
  for(i = 0, t = *(unsigned*)&mask; !(t & 1); i ++, t >>= 1);
  printf("--call_backed on CPU %d\n", i);
}

int main()
{
  int ret;
  ret = nids_init();
  printf("Init return %d.\n",ret);
  nids_register_ip_frag(msg_print);
  nids_run();
  puts("Test has reached the end.");
  return 0;
}
