#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		gl_strlen(char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
void	shift(char *read_buffer);

#endif