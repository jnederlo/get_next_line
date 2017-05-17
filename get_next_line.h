
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>

# include <fcntl.h> /////////

# define BUFF_SIZE 8

int		get_next_line(const int fd, char **line);
int		open_file(char *file);
int		nl_hunter(char *buf, char *temp, char **line, const int fd);
char	*buf_trim(char *buf, int i, size_t buf_size);
int		check_buf(char *buf, char **line);

#endif
