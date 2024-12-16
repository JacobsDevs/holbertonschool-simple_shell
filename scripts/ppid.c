#include <unistd.h>
#include <stdio.h>

int main(void)
{
	printf("%u\n", getppid());
	return (0);
}
