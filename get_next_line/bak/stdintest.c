#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

int main(void)
{
	int ret;
	char *line;

	ret = 1;
//	fd = open(argv[1], O_RDONLY);
//	if (fd == -1)
//	{
//		printf("open() error\n");
//		return (1);
//	}
//	printf("File open, fd: [%d]\n", fd);
	line = get_next_line(STDIN_FILENO);
//	line = get_next_line(STDIN_FILENO);
//	line = get_next_line(STDIN_FILENO);
//	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(STDIN_FILENO);
	}
	return (0);
}
