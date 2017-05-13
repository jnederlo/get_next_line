

#include "get_next_line.h"
#include <stdio.h>

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	int			check;
	int			i;

	i = 0;

	if (argc != 2)
		return (0);

	fd = open_file(argv[1]);
//	read_ret = read(fd, buf, BUFF_SIZE);
//	printf("%s\n", buf);
//	printf("%d\n", read_ret);

//	get_next_line(fd, &line);
//	printf("This is what is in 'line':%s\n", line);
//	get_next_line(fd, &line);
//	printf("This is what is in 'line':%s\n", line);
	while ((check = get_next_line(fd, &line)) == 1)
	{

		printf("-----------%s\n", line);
		line++;
	}
	if (check == -1)
		printf("ERROR\n");
	if (check == 0)
		printf("DONE\n");

	return (0);
}


