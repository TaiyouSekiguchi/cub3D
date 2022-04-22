#include "cub3D.h"

static int	comma_count(char *rgb)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (rgb[i] != '\0')
	{
		if (rgb[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	set_color(int *color, char *rgb)
{
	char	**split_rgb;
	int		red;
	int		green;
	int		blue;

	if (rgb == NULL || comma_count(rgb) != 2)
		error_exit(NULL, "cub3D : Color format \"F(C) R,G,B\"");
	if (*color != -1)
		error_exit(NULL, "cub3D : Color is already set");
	split_rgb = ft_split(rgb, ',');
	if (split_rgb == NULL)
		error_exit("malloc", NULL);
	if (ft_split_size(split_rgb) != 3)
		error_exit(NULL, "cub3D : Color format \"F(C) R,G,B\"");
	red = color_atoi(split_rgb[0]);
	green = color_atoi(split_rgb[1]);
	blue = color_atoi(split_rgb[2]);
	if (red > COLOR_MAX || green > COLOR_MAX || blue > COLOR_MAX)
		error_exit(NULL, "cub3D : Color range 0~255");
	*color = create_trgb(0, red, green, blue);
	ft_split_free(split_rgb);
}
