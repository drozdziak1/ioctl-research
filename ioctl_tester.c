#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <stropts.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd;

	char *fname, *arg;

	if (argc < 3)
		return EINVAL;

	fname = argv[1];
	arg = argv[2];

	fd = open(fname, O_WRONLY);

	if(fd == -1)
		return errno;

	printf("Ready to ioctl(%s, I_STR, %s)\n", fname, arg);

	close(fd);

	return 0;
}
