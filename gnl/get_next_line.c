/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 13:23:08 by jnederlo          #+#    #+#             */
/*   Updated: 2017/03/15 16:48:17 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static char	buf[BUFF_SIZE];
	char		*temp;
	int			i;

	i = -1;
	if (!line)
		return (-1);
	if ((temp = ft_strnew(BUFF_SIZE)) == 0)
		return (-1);
	while (buf[++i])
	{
		if (buf[i] == '\n')
		{
			temp = ft_strncpy(temp, buf, i);
			*line = temp;
			*buf = *buf_trim(buf, (i + 1), BUFF_SIZE);
			return (1);
		}
	}
	i = nl_hunter(buf, temp, line, fd);
	if (i == 1)
		return (1);
	else if (i == 0)
		return (0);
	return (-1);
}

char	*line_trim(char *temp)
{
	int			i;
	char		*new_temp;

	i = 0;
	while (temp[i] != '\n')
		i++;
	new_temp = ft_strsub(temp, 0, i);
	free(temp);
	temp = new_temp;
	return (temp);
}

char	*buf_trim(char *buf, int i, int buf_size)
{
	int			k;
	char		*holder;
	int			size;

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
	buf = ft_strcpy(buf, holder);
	free(holder);
	return (buf);
}

int		nl_hunter(char *buf, char *temp, char **line, const int fd)
{
	int			check;
	int			read_ret;
	char		*new_temp;

	new_temp = NULL;
	new_temp = ft_strjoin(temp, buf);
	free(temp);
	temp = new_temp;
	ft_bzero(buf, BUFF_SIZE);
	while ((read_ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		new_temp = ft_strjoin(temp, buf);
		free(temp);
		temp = new_temp;
		if ((check = buf_check(buf, temp, line, read_ret)) == 1)
			return (1);
		ft_bzero(buf, BUFF_SIZE);
	}
	if (read_ret == 0 && ft_strlen(temp) > 0)
	{
		*line = temp;
		ft_bzero(buf, BUFF_SIZE);
		return (1);
	}
	return (read_ret);
}

int		buf_check(char *buf, char *temp, char **line, int read_ret)
{
	int			i;

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
	return (0);
}
