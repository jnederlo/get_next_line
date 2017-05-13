
#include "get_next_line.h"
#include <stdio.h> // REMOVE THIS!!!

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE];
	int			read_ret;
	char		*temp;
	size_t		size;

	if ((temp = ft_strnew(BUFF_SIZE)) == 0)
		return (-1);
	read_ret = nl_hunter(buf, temp, line, fd);
	printf("'read_ret' = %d\n", read_ret);
	if (read_ret > 0)
		return (1);
	else if (read_ret == 0 && *buf)
	{
		*line = buf;
		printf("THE LINE:	%s\n", *line);
		ft_bzero(buf, BUFF_SIZE);
		return (1);
	}
/*
	else if (*buf)
	{
		size = ft_strlen(buf);
		buf_hunter(buf, line, size);
		printf("THE LINE:	%s\n", *line);
		return (1);
	}*/
	else if (read_ret == 0)
		return (0);
	else
		return (-1);
}

char	*line_trim(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i] != '\n')
		i++;
	temp = ft_strsub(temp, 0, i);
	return (temp);
}

char	*buf_trim(char *buf, int i, size_t buf_size)
{
	int		k;
	char	*holder;
	int		size;

	size = buf_size - i;
	if ((holder = ft_strnew(size)) == 0)
		return (0);
	k = 0;
	while (i < buf_size)
	{
		holder[k] = buf[i];
		k++;
		i++;
	}
	ft_bzero(buf, buf_size);
	buf = ft_strncpy(buf, holder, size);
	return (buf);
}

int	nl_hunter(char *buf, char *temp, char **line, const int fd)
{
	int		i;
	size_t	read_ret;

	temp = ft_strjoin(temp, buf);
	while ((read_ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		temp = ft_strjoin(temp, buf);
		i = 0;
		while (i < BUFF_SIZE)
		{
			if (buf[i] == '\n')
			{
				temp = line_trim(temp);
				*line = temp;
				buf = buf_trim(buf, (i + 1), read_ret);
				return (1);
			}
			i++;
		}
	}
	return (read_ret);
}

int	buf_hunter(char *buf, char **line, size_t size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (buf[i] == '\n')
		{
			buf = buf_trim(buf, (i + 1), size);
			*line = buf;
			return (1);
		}
		i++;
	}
	*line = buf;
	ft_bzero(buf, BUFF_SIZE);
	return (0);
}
