#include "cub3D.h"

#define ERR_MSG "cub3D : Wrong format \"[identifier] [information]\""

static void	do_mlx_xpm_file_to_image(t_game *game, char *path, int num)
{
	void	**img;
	int		*width;
	int		*height;

	img = &game->imgs[num].img;
	width = &game->imgs[num].width;
	height = &game->imgs[num].height;
	*img = mlx_xpm_file_to_image(game->mlx, path, width, height);
	if (*img == NULL)
		error_exit("mlx", NULL);
}

static void	do_mlx_get_data_addr(t_game *game, int num)
{
	void	**img;
	int		**data;
	int		*bpp;
	int		*line_len;
	int		*endian;

	img = &game->imgs[num].img;
	data = &game->imgs[num].data;
	bpp = &game->imgs[num].bpp;
	line_len = &game->imgs[num].line_len;
	endian = &game->imgs[num].endian;
	*data = (int *)mlx_get_data_addr(*img, bpp, line_len, endian);
	if (*data == NULL)
		error_exit("mlx", NULL);
}

int	set_texture(t_game *game, char *path, int num)
{
	if (path == NULL)
		error_exit(NULL, "cub3D : Texture format \"NO(SO, WE, EA) file_path\"");
	if (game->imgs[num].img != NULL)
		error_exit(NULL, "cub3D : Texture path is already set");
	do_mlx_xpm_file_to_image(game, path, num);
	do_mlx_get_data_addr(game, num);
}
