#include "cub3D.h"

static void		my_swap(t_pair *a, t_pair *b)
{
	double	tmp_first;
	int		tmp_second;

	tmp_first = a->first;
	tmp_second = a->second;

	a->first = b->first;
	a->second = b->second;
	b->first = tmp_first;
	b->second = tmp_second;
}

static int		pivot(t_pair *sprites, int i, int j)
{
	int k = i + 1;
	while (k <= j && sprites[i].first == sprites[k].first)
		k++;
	if (k > j)
		return (-1);
	if (sprites[i].first >= sprites[k].first)
		return (i);
	return (k);
}

static int		partition(t_pair *sprites, int i, int j, double x)
{
	int l = i;
	int r = j;

	while (l <= r)
	{
		while (l <= j && sprites[l].first < x)
			l++;
		while (r >= i && sprites[r].first >= x)
			r--;
		if (l > r)
			break ;
		my_swap(&sprites[l], &sprites[r]);
		l++;
		r--;
	}
	return (l);
}

static void		quickSort(t_pair *sprites, int i, int j)
{
	if (i == j)
		return ;
	int p = pivot(sprites, i, j);
	if (p != -1)
	{
		int k = partition(sprites, i, j, sprites[p].first);
		quickSort(sprites, i ,k - 1);
		quickSort(sprites, k, j);
	}
}

void			sortSprites(int *order, double *dist, int amount)
{
	t_pair	sprites[amount];

	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}

	quickSort(sprites, 0, amount - 1);
	
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}
