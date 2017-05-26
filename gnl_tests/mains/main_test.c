#include "get_next_line.h"

#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd1;
	int fd2;
	int check1;
	int check2;
	char *line;

    if (argc > 3)
        return (0);

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 != -1)
		printf("OPEN 1 SUCCESS!\n");
	else
		printf("OPEN 1 FAILED!\n");

	if (fd2 != -1)
		printf("OPEN 2 SUCCESS!\n");
	else
		printf("OPEN 2 FAILED!\n");



	// READ FD2
	if((check2 = get_next_line(fd2, &line)) == 1)
	{
		printf("FD2:\t%s\n", line);
	}
	if (check2 == -1)
		printf("ERROR 2!\n");
	if (check2 == 0)
		printf("DONE READING 2!\n");
	
	// READ FD1
	while((check1 = get_next_line(fd1, &line)) == 1)
	{
		printf("line: %s\n", line);
	}
	if (check1 == -1)
		printf("ERROR 1!\n");
	if (check1 == 0)
		printf("DONE READING 1!\n");

	// READ FD2
	if((check2 = get_next_line(fd2, &line)) == 1)
	{
		printf("FD2:\t%s\n", line);
	}
	if (check2 == -1)
		printf("ERROR 2!\n");
	if (check2 == 0)
		printf("DONE READING 2!\n");
	
	//READ FD1
	if((check1 = get_next_line(fd1, &line)) == 1)
	{
		printf("FD1: %i\n%s\n", fd1, line);
	}
	if (check1 == -1)
		printf("ERROR 1!\n");
	if (check1 == 0)
		printf("DONE READING 1!\n");

	// // READ FD2
	if((check2 = get_next_line(fd2, &line)) == 1)
	{
		printf("FD2:\t%s\n", line);
	}
	if (check2 == -1)
		printf("ERROR 2!\n");
	if (check2 == 0)
		printf("DONE READING 2!\n");

	// // READ FD1
	if((check1 = get_next_line(fd1, &line)) == 1)
	{
		printf("FD1: %i\n%s\n", fd1, line);
	}
	if (check1 == -1)
		printf("ERROR 1!\n");
	if (check1 == 0)
		printf("DONE READING 1!\n");

	close(fd1);
	close(fd2);
	return(0);
}