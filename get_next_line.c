
#include "get_next_line.h"
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE];
	int			read_ret;
	char		*temp;

	if ((read_ret = check_buf(buf, line)) == 1)
		return (1);
	if ((temp = ft_strnew(BUFF_SIZE)) == 0)
		return (-1);
	read_ret = nl_hunter(buf, temp, line, fd);
	if (read_ret == 1)
		return (1);
	if (read_ret == 0)
		return (0);
	return (-1);
}

int	check_buf(char *buf, char **line)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(buf);
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			ft_bzero(*line, size);
			*line = ft_strncpy(*line, buf, i);
			buf = buf_trim(buf, (i + 1), size);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*line_trim(char *temp)
{
	int	i;

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
	while (i < (int)buf_size)
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
	printf("BUF CONTAINS:	%s\n", buf);
	while ((read_ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		printf("READ_RET EQUALS:	%zu\n", read_ret);
		if (read_ret < BUFF_SIZE)
			//NEED TO TRIM BUF HERE...
		printf("BUF NOW CONTAINS:	%s\n", buf);
		temp = ft_strjoin(temp, buf);
		i = 0;
		while (i < BUFF_SIZE)
		{
			if (buf[i] == '\n')
			{
				temp = line_trim(temp);
				*line = temp;
				buf = buf_trim(buf, (i + 1), read_ret);
				printf("BUF IS NOW TRIMMED TO:	%s/n", buf);
				return (1);
			}
			i++;
		}
	}
	if (read_ret == 0 && ft_strlen(temp) > 0)
	{
		*line = temp;
		ft_bzero(buf, ft_strlen(buf));
		return (1);
	}
	return (read_ret);
}
