#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

int check_argc(int argc)
{
	if (argc < 2)
	{
		printf("File names missing.\n");
		return (0);
	}
	return (1);
}

int endcheck(int eof[50])
{
	int ret = 0;
	for (int i = 0; i < eof[0]; i++)
		if (eof[i + 1] == 1)
			ret++;
	return (ret);
}

int main(int argc, char **argv)
{
	int i;
	int fd[50];
	int eof[50];
	int ret;
	char *line;

	for (int j = 0; j < argc; j++)
		eof[j] = 0;
	ret = 1;
	i = argc;
	if (check_argc(argc) == 0)
		return (0);
	fd[0] = 0;
	for (int j = 1; j < argc; j++)
	{
		printf("argv[%d] = [%s]\n", j, argv[j]);
		fd [j] = open(argv[j], O_RDONLY);
		if (fd[j] == -1)
		{
			printf("open() error, file [%s]\n", argv[j]);
			return (1);
		}
		fd[0]++;
	}
	eof[0] = fd[0];
//	printf("File open, fd: [%d]\n", fd);
//	printf("fd[0] = [%d]\n", fd[0]);
//	printf("file id at fd[fd[0]] : [%d]\n", fd[fd[0]]);
	while (endcheck(eof) != eof[0])
	{
//		printf("eofcheck: [%d] eof[0]: [%d]\n", endcheck(eof), eof[0]);
		for (int j = 0; j < fd[0]; j++)
		{
			line = get_next_line(fd[j + 1]);
			if (line == NULL)
				eof[j + 1] = 1;
			else
				printf("%s", line);
		}
		
	}
	for (int j = 0; j < fd[0]; j++)
		if (close(fd[j + 1]) == -1)
			printf("close error, file [%s]\n", argv[j + 1]);
	return (0);
}
