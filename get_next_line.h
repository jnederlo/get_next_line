
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdlib.h>

# include <fcntl.h> /////////

# define BUFF_SIZE 32

int		get_next_line(const int fd, char **line);
char	*line_trim(char *temp);
int		main(int argc, char **argv);
int		open_file(char *file);
int		nl_hunter(char *buf, char *temp, char **line, const int fd);
int		buf_hunter(char *buf, char **line, size_t size);
char	*buf_trim(char *buf, int i, size_t buf_size);

#endif
