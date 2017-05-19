/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnederlo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 13:23:08 by jnederlo          #+#    #+#             */
/*   Updated: 2017/03/15 16:48:17 by jnederlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>

# define BUFF_SIZE 2048

int		get_next_line(const int fd, char **line);
char	*line_trim(char *temp);
int		nl_hunter(char *buf, char *temp, char **line, const int fd);
char	*buf_trim(char *buf, int i, int buf_size);
int		buf_check(char *buf, char *temp, char **line, int read_ret);

#endif
