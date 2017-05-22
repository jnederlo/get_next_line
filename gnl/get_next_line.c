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

#include <stdio.h>

int		get_next_line(const int fd, char **line)
{
	char			*temp;
	int				i;
	static t_gnl	*head;
	t_gnl			*node;

	i = -1;
	if (!line)
		return (-1);
	if (head == NULL)
		head = gnl_list(head, fd);
	node = gnl_list(head, fd);
	if ((temp = ft_strnew(BUFF_SIZE)) == 0)
		return (-1);
	while (node->buf[++i])
	{
		if (node->buf[i] == '\n')
		{
			temp = ft_strncpy(temp, node->buf, i);
			*line = temp;
			*node->buf = *ft_linestrip(node->buf, '\n');
			return (1);
		}
	}
	i = nl_hunter(node->buf, temp, line, fd);
	if (i == 1)
		return (1);
	else if (i == 0)
		return (0);
	return (-1);
}

char	*ft_linestrip(char *s, char c)
{
	int		i;
	int		size;
	int		k;
	char	*s1;

	size = ft_strlen(s);
	i = 0;
	while (s[i] != c && s[i])
		i++;
	i++;
	if ((s1 = ft_strnew(size - i)) == 0)
		return (0);
	k = 0;
	while (i < size)
		s1[k++] = s[i++];
	ft_bzero(s, size);
	s = ft_strcpy(s, s1);
	free(s1);
	return (s);
}

// char	*buf_trim(char *buf, int i, int buf_size)
// {
// 	int			k;
// 	char		*holder;
// 	int			size;

// 	size = buf_size - i;
// 	if ((holder = ft_strnew(size)) == 0)
// 		return (0);
// 	k = 0;
// 	while (i < buf_size)
// 	{
// 		holder[k] = buf[i];
// 		k++;
// 		i++;
// 	}
// 	ft_bzero(buf, buf_size);
// 	buf = ft_strcpy(buf, holder);
// 	free(holder);
// 	return (buf);
// }

int		nl_hunter(char *buf, char *temp, char **line, const int fd)
{
	int			check;
	int			read_ret;
	char		*new_temp;

	new_temp = NULL;
	new_temp = ft_strjoin(temp, buf);
	free(temp);
	temp = new_temp;
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((read_ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		new_temp = ft_strjoin(temp, buf);
		free(temp);
		temp = new_temp;
		if ((check = buf_check(buf, temp, line)) == 1)
			return (1);
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (read_ret == 0 && ft_strlen(temp) > 0)
	{
		*line = temp;
		ft_bzero(buf, BUFF_SIZE + 1);
		return (1);
	}
	return (read_ret);
}

int		buf_check(char *buf, char *temp, char **line)
{
	int			i;

	i = 0;
	while (i < BUFF_SIZE)
	{
		if (buf[i] == '\n')
		{
			temp = ft_linetrim(temp, '\n');
			*line = temp;
			buf = ft_linestrip(buf, '\n');
			return (1);
		}
		i++;
	}
	return (0);
}

t_gnl	*gnl_list(t_gnl *head, int fd)
{
	t_gnl		*node;

	if (head == NULL)
	{
		if (!(node = (t_gnl *)malloc(sizeof(t_gnl))))
			return (0);
		node->fd = fd;
		ft_bzero(node->buf, BUFF_SIZE + 1);
		node->next = NULL;
		return (node);
	}
	while (fd != head->fd && head->next != NULL)
		head = head->next;
	if (fd == head->fd)
		return (head);
	if (!(node = (t_gnl *)malloc(sizeof(t_gnl))))
		return (0);
	node->fd = fd;
	ft_bzero(node->buf, BUFF_SIZE + 1);
	head->next = node;
	node->next = NULL;
	return (node);
}
