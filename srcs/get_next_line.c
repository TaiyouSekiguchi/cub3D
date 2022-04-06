#include "get_next_line.h"

#define BUFFER_SIZE 32
//#define DEBUG 1

int		save_check(char **line, char **save)
{
	char	*tmp;
#ifdef DEBUG
	printf("*****save_check part*****\n");
#endif
	*line = my_strdup(*save, '\n');
	tmp = my_strdup(my_strchr(*save, '\n') + 1, '\0');
	free(*save);
	if (*line == NULL || tmp == NULL)
	{
#ifdef DEBUG
		printf("save_check malloc failed. return -1\n");
#endif
		return (-1);
	}
	*save = tmp;
#ifdef DEBUG
	printf("*line is %s\n", *line);
	printf("*save is %s\n", *save);
	printf("*****save_check part*****\n");
#endif
	return (1);
}

char	*empty_string(char *s)
{
	char	*ret;

	if (s != NULL)
		return (s);
	else
	{
		ret = (char *)malloc(sizeof(char));
		if (ret == NULL)
			return (NULL);
		*ret = '\0';
	}
	return (ret);
}

int		my_buffering(int fd, char **line, char **save)
{
	char	*buf;
	int		ret;

#ifdef DEBUG
	printf("*****my_buffering part*****\n");
#endif
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (my_strchr(buf, '\n') == NULL)
			*save = my_strjoin(*save, buf, '\0');
		else
		{
			*line = my_strjoin(*save, buf, '\n');
			*save = my_strdup(my_strchr(buf, '\n') + 1, '\0');
			break ;
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
#ifdef DEBUG
	printf("ret   is %d\n", ret);
	printf("*line is %s\n", *line);
	printf("*save is %s\n", *save);
	printf("*****my_buffering part*****\n");
#endif
	if (ret > 0 && (*line == NULL || *save == NULL))
		ret = -1;
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char		*save;
	int				ret;

	if (fd <= -1 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (my_strchr(save, '\n') != NULL)
		return (save_check(line, &save));
	save = empty_string(save);
	if (save == NULL)
		return (-1);
	ret = my_buffering(fd, line, &save);
	if (ret > 0)
		ret = 1;
	if (ret == 0)
	{
		*line = my_strdup(save, '\0');
		free(save);
		save = NULL;
	}
#ifdef DEBUG
	printf("*****gnl part*****\n");
	printf("*line is %s\n", *line);
	printf("save  is %s\n", save);
	printf("*****gnl part*****\n");
#endif
	if (*line == NULL)
		ret = -1;
	return (ret);
}
