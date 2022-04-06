#include "cub3D.h"

int		main_loop(t_game *game)
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	double		time;
	double		oldTime;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			x;
	int			y;
	int			w;
	int			h;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	unsigned int			color;
	double		*ZBuffer;
	int			*spriteOrder;
	double		*spriteDistance;

	spriteOrder = (int *)malloc(sizeof(int) * game->map_cnt.sprite_cnt);
	spriteDistance = (double *)malloc(sizeof(double) * game->map_cnt.sprite_cnt);
	ZBuffer = (double *)malloc(sizeof(double) * game->file.screenWidth);

	unsigned int texture[11][texWidth * texHeight];
	for (x = 0; x < 11; x++)
	{
		for (y = 0; y < texWidth * texHeight; y++)
		{
			texture[x][y] = game->imgs[x].data[y];
		}
	}

	w = 640;
	h = 480;
	//img_init(game);

	for (y = game->file.screenHeight / 2 + 1; y < game->file.screenHeight; ++y)
	{
		float rayDirX0 = game->player.dirX - game->player.planeX;
		float rayDirY0 = game->player.dirY - game->player.planeY;
		float rayDirX1 = game->player.dirX + game->player.planeX;
		float rayDirY1 = game->player.dirY + game->player.planeY;

		int p = y - game->file.screenHeight /2;

		float posZ = 0.5 * game->file.screenHeight;

		float rowDistance = posZ / p;

		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / game->file.screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / game->file.screenWidth;

		float floorX = game->player.posX + rowDistance * rayDirX0;
		float floorY = game->player.posY + rowDistance * rayDirY0;
      
		for(x = 0; x < game->file.screenWidth; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
			
			floorX += floorStepX;
			floorY += floorStepY;
			
			// choose texture and draw the pixel
			//int checkerBoardPattern = (int)(cellX + cellY) & 1;
			//int floorTexture;
			//if(checkerBoardPattern == 0) floorTexture = 3;
			//else floorTexture = 4;
			int floorTexture = 3;
			int ceilingTexture = 6;
			
			// floor
			//color = texture[floorTexture][texWidth * ty + tx];
			//color = 0x00FF0000;
			color = game->file.floor;
			//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(&game->img, x, y, color);
			//buffer[y][x] = color;
			
			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			//color = texture[ceilingTexture][texWidth * ty + tx];
			//color = 0x00FF0000;
			color = game->file.ceil;
			//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(&game->img, x, game->file.screenHeight - y - 1, color);
			//buffer[screenHeight - y - 1][x] = color;
		}
	}

	for (x = 0; x < w; x++)
	{
		cameraX = 2 * x / (double)w - 1;
		rayDirX = game->player.dirX + game->player.planeX * cameraX;
		rayDirY = game->player.dirY + game->player.planeY * cameraX;
		mapX = (int)game->player.posX;
		mapY = (int)game->player.posY;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.posX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - game->player.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->player.posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(h / perpWallDist);

		drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		//int texNum = game->worldMap[mapX][mapY] - 1;
		int texNum;
		if (side == 0)
		{
			if (rayDirX < 0)
				texNum = 1;
			else
				texNum = 3;
		}
		else
		{
			if (rayDirY < 0)
				texNum = 2;
			else
				texNum = 0;
		}

		double wallX;
		if (side == 0)
			wallX = game->player.posY + perpWallDist * rayDirY;
		else
			wallX = game->player.posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)(texWidth));
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;

		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		for (y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			color = texture[texNum][texHeight * texY + texX];
			if (side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&game->img, x, y, color);
		}

		ZBuffer[x] = perpWallDist;
	}

	for (int i = 0; i < game->map_cnt.sprite_cnt; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((game->player.posX - game->sprite[i].x) * (game->player.posX - game->sprite[i].x) + (game->player.posY - game->sprite[i].y) * (game->player.posY - game->sprite[i].y));
	}

	sortSprites(spriteOrder, spriteDistance, game->map_cnt.sprite_cnt);

	for (int i = 0; i < game->map_cnt.sprite_cnt; i++)
	{
		double spriteX = game->sprite[spriteOrder[i]].x - game->player.posX;
		double spriteY = game->sprite[spriteOrder[i]].y - game->player.posY;

		double invDet = 1.0 / (game->player.planeX * game->player.dirY - game->player.dirX * game->player.planeY);

		double transformX = invDet * (game->player.dirY * spriteX - game->player.dirX * spriteY);
		double transformY = invDet * (-game->player.planeY * spriteX + game->player.planeX * spriteY);

		int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

#define uDiv 1
#define vDiv 1
#define vMove 0.0

		int vMoveScreen = (int)(vMove / transformY);

		int spriteHeight = abs((int)(h / transformY)) / vDiv;

		int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
		if (drawEndY >= h)
			drawEndY = h - 1;

		int spriteWidth = abs((int) (h / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= w) drawEndX = w - 1;

		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				color = texture[game->sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0)
					//buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					my_mlx_pixel_put(&game->img, stripe, y, color);
			}
		}
	}
	//do_save(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	free(spriteOrder);
	free(spriteDistance);
	free(ZBuffer);
	return (0);
}