#include<sys/types.h>
#include<sys/stat.h>
int main ()
{
creat("test.txt",S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH|S_IWOTH|S_IXOTH);
return 0;
}
