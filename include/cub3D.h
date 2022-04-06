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
#define KEY_LEFT 123
#define KEY_RIGHT 124

#define KEY_PRESS 2
#define DESTROY_NOTIFY 17
#define NO_EVENT_MASK 0L

#define FILE_TYPE 0x4D42
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

//#define screenWidth 640
//#define screenHeight 480

#define mapWidth 24
#define mapHeight 24


typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_Sprite
{
	double		x;
	double		y;
	int			texture;
}				t_Sprite;

#pragma pack(2)
typedef struct	BITMAPFILEHEADER
{
	u_int16_t	bfType;
	u_int32_t	bfSize;
	u_int16_t	bfReserved1;
	u_int16_t	bfReserved2;
	u_int32_t	bfOffBits;
}				BITMAPFILEHEADER;
#pragma pack()

typedef struct	BITMAPINFOHEADER
{
	u_int32_t	biSize;
	int32_t		biWidth;
	int32_t		biHeight;
	u_int16_t	biPlanes;
	u_int16_t	biBitCount;
	u_int32_t	biCompression;
	u_int32_t	biSizeImage;
	int32_t		biXPelsPerMeter;
	int32_t		biYPelsPerMeter;
	u_int32_t	biClrUsed;
	u_int32_t	biClrImportant;
}				BITMAPINFOHEADER;

typedef struct	s_file
{
	int			screenWidth;
	int			screenHeight;
	int			floor;
	int			ceil;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	char		*map;
}				t_file;

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
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_player;

typedef struct	s_counter
{
	int			map_max_len;
	int			map_line_cnt;
	int			sprite_cnt;
}				t_counter;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		imgs[11];
	t_player	player;
	t_file		file;
	t_counter	map_cnt;
	t_Sprite	*sprite;
	int			**worldMap;
}				t_game;


unsigned int	create_trgb(int t, int r, int g, int b);
u_int8_t		get_t(unsigned int trgb);
u_int8_t		get_r(unsigned int trgb);
u_int8_t		get_g(unsigned int trgb);
u_int8_t		get_b(unsigned int trgb);

void			sortSprites(int *order, double *dist, int amount);

int				deal_key(int key_code, t_game *game);

int				my_mlx_pixel_put(t_img *img, int x, int y, int color);
int				my_close(t_game *game);
int				main_loop(t_game *game);


#endif
