#include "parsing.h"

int	init_pipe(int *fd)
{
	if (pipe(fd) != 0)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}
