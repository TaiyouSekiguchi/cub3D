#include "cub3D.h"

static void	read_file_exit(int fd, char *msg)
{
	close(fd);
	error_exit(NULL, msg);
}

static int file_open(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("open", NULL);
	return (fd);
}

static void	gnl_loop(int fd, t_list **list)
{
	char	*line;
	int		ret;
	t_list	*new;

	*list = NULL;
	ret = get_next_line(fd, &line);
	if (ret == END)
		read_file_exit(fd, "get_next_line : Read empty file");
	if (ret == ERROR)
		read_file_exit(fd, "get_next_line : failed");
	while (ret > 0)
	{
		new = ft_lstnew(line);
		if (new == NULL)
		{
			close(fd);
			error_exit("malloc", NULL);
		}
		ft_lstadd_back(list, new);
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
			read_file_exit(fd, "get_next_line : failed");
	}
	if (line[0] == '\0')
	{
		free(line);
		line = NULL;
	}
	else
	{
		new = ft_lstnew(line);
		if (new == NULL)
		{
			close(fd);
			error_exit("malloc", NULL);
		}
		ft_lstadd_back(list, new);
	}
}

void	read_file(char *file_name, t_list **list)
{
	int		fd;
	int		ret;
	char	*line;

	fd = file_open(file_name);
	gnl_loop(fd, list);
	close(fd);
}
