#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

int check_argc(int argc)
{
	if (argc == 1)
	{
		printf("File name missing.\n");
		return (0);
	}
	if (argc > 2)
	{
		printf("Too many arguments.\n");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	int ret;
	char *line;

	ret = 1;
	if (check_argc(argc) == 0)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("open() error\n");
		return (1);
	}
//	printf("File open, fd: [%d]\n", fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		printf("close () error\n");
		return (1);
	}
	return (0);
}
