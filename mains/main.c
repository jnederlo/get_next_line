

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

	i = (int)argv[1];
	i = 1;
	if (argc < 0)
		return (0);
	fd = open_file(argv[1]);
//	fd = 1;
//	write(fd, "efghijkl", 8);
//	close(fd);
	while ((check = get_next_line(fd, &line)) == 1)
	{	
		printf("[%d]%s\n", i, line);
		i++;
	}
	if (check == -1)
		printf("ERROR\n");
	if (check == 0)
		printf("DONE\n");
	return (0);
}


