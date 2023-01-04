#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../get_next_line.h"

char *itoa(int, char *, size_t);

int endcheck(int eof[131072])
{
	int ret = 0;
	for (int i = 0; i < eof[0]; i++)
		if (eof[i + 1] == 1)
			ret++;
	return (ret);
}

int main(int argc, char **argv)
{
	int files, lines, ret;
	int fd[131072];
	int eof[131072];
	char *line;
	char file[13] = { 't','s','t','t','x','t','\0','\0','\0','\0','\0','\0','\0'};

	if (argc < 2 || atoi(argv[1]) < 1 || argc > 3 || (argc == 3 && atoi(argv[2]) < 1))
	{
		printf("Usage: gentest files [lines]\nTests [files] number of tsttxt? files. Outputs all lines by default but if [lines] is specified, outputs only the first number  [lines] in each file.\n");
		return (-1);
	}

	files = atoi(argv[1]);
	if (argc == 3)
		lines = atoi(argv[2]);

	for (int i = 0; i < files; i++)
	{
		itoa(i + 1, file+6, 10);
		fd[i] = open(file, O_RDONLY);
		if (fd[i] == -1)
		{
			printf("open() error, file [%s]\n", file);
			return (1);
		}
	}
	for (int i = 0; i < files; i++)
		eof[i] = 0;

	ret = 0;

	while (ret < files && (argc == 2 || lines > 0))
	{
//		printf("eofcheck: [%d] eof[0]: [%d]\n", endcheck(eof), eof[0]);
		for (int i = 0; i < files; i++)
		{
//			printf("Calling get_next_line with fd [%d]\n", fd[j + 1]);
			if (eof[i] == 0)
				line = get_next_line(fd[i]);
//			system("read -r -s -d ' '"); // read space
//			system("sleep 0.6");
			if (eof[i] == 0 && line == NULL)
			{
				eof[i] = 1;
				ret++;
			}
			else
				printf("%s", line);
		}
		lines--;
		
	}
	for (int i = 0; i < files; i++)
		if (close(fd[i]) == -1)
			printf("close error, file [%s]\n", itoa(i, file+6, 10));
	return (0);
}
