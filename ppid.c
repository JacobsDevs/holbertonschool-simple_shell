#include <unistd.h>
#include <stdio.h>

int ppid(void)
{
	printf("%u\n", getppid());
	return (0);
}
