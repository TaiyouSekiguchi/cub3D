#include "cub3D.h"

void	read_file(char *file_name, t_list **list)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("open", NULL);

	*list = NULL;
	ret = get_next_line(fd, &line);
	if (ret == END)
		error_exit(NULL, "Read empty file");
	if (ret == ERROR)
		error_exit(NULL, "GNL failed");
	while (ret > 0)
	{
		ft_lstadd_back(list, ft_lstnew(line));
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
			error_exit(NULL, "GNL failed");
	}
	free(line);
	close(fd);
}
