#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mlx.h"
#include "get_next_line.h"
#include "libft.h"

#define PI 3.14159265359

#define FLOOR_HORIZONTAL 1
#define texWidth 64
#define texHeight 64

#define RGB_Red 0x00FF0000
#define RGB_Green 0x0000FF00
#define RGB_Blue 0x000000FF
#define RGB_White 0x00FFFFFF
#define RGB_Yellow 0x00FFFF00

#define KEY_ESC 0xff1b
#define KEY_W 0x77
#define KEY_S 0x73
#define KEY_A 0x61
#define KEY_D 0x64
#define KEY_LEFT 0xff51
#define KEY_RIGHT 0xff53

#define KEY_PRESS 2
#define DESTROY_NOTIFY 17
#define NO_EVENT_MASK 0L

#define FILE_TYPE 0x4D42
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

#define mapWidth 24
#define mapHeight 24

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	int			**world_map;
	int			row;
	int			col;
	t_player	player;
	t_img		img;
	t_img		imgs[4];
	int			floor;
	int			ceil;
}				t_game;

//prototype declare (filename alphabet order)

//close_check.c
int		close_check(t_game *game, int **map, int x, int y);


//color.c
unsigned int	create_trgb(int t, int r, int g, int b);
u_int8_t		get_t(unsigned int trgb);
u_int8_t		get_r(unsigned int trgb);
u_int8_t		get_g(unsigned int trgb);
u_int8_t		get_b(unsigned int trgb);

//deal_key.c
int				deal_key(int key_code, t_game *game);

//error_exit.c
void			error_exit(char *cmd, char *msg);

//init.c
void			game_init(t_game *game);

//extension_check.c
int				extension_check(char *file_path);

//file_info_parse.c
void			file_info_parse(t_game *game, t_list *list, char *news);

//game_free.c
void			game_free(t_game *game);

//main_loop.c
int				main_loop(t_game *game);

//make_map.c
void			make_map(t_game *game, t_list *list, char *news);

//map_check.c
int				map_check(t_game *game);

//read_file.c
void			read_file(char *file_name, t_list **list);

//utils.c
int				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				my_close(t_game *game);

#endif
