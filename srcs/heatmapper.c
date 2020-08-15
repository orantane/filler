/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heatmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:16:18 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 17:19:42 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static int		check_zero(t_filler *filler, t_block *map, int x, int y)
{
	if ((x + 1) < map->width && filler->heat[y][x + 1] == OPPO)
		return (0);
	if ((x - 1) >= 0 && filler->heat[y][x - 1] == OPPO)
		return (0);
	if ((y + 1) < map->height && filler->heat[y + 1][x] == OPPO)
		return (0);
	if ((y - 1) >= 0 && filler->heat[y - 1][x] == OPPO)
		return (0);
	return (PLAY);
}

/*
** Checks around the current position to find the correct value for that
** position. Needs to have 0's around the opponent for this to work. This
** function needs to be added.
*/

static int		check_value(t_filler *filler, t_block *map, int x, int y)
{
	int		value;
	int		arr[4];
	int		i;

	i = -1;
	value = 1000;
	if (filler->heat[y][x] == PLAY)
		return (PLAY);
	if (filler->heat[y][x] == OPPO)
		return (OPPO);
	if ((x + 1) < map->width)
		arr[0] = filler->heat[y][x + 1] + 1;
	if ((x - 1) >= 0)
		arr[1] = filler->heat[y][x - 1] + 1;
	if ((y + 1) < map->height)
		arr[2] = filler->heat[y + 1][x] + 1;
	if ((y - 1) >= 0)
		arr[3] = filler->heat[y - 1][x] + 1;
	arr[4] = check_zero(filler, map, x, y);
	while (++i < 5)
	{
		if (arr[i] < value)
			value = arr[i];
	}
	return (value);
}

t_filler	*give_value(t_filler *filler, t_block *map, int dir)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (filler->heat[y][x] == PLAY) // Skips the players positions.
				x++;
			if (filler->heat[y][x] == OPPO) // Marks zeroes around the opponent positions.
			{
				if (map->width > (x + dir) && (x + dir) >= 0 && filler->heat[y][x + dir] < PLAY)
					filler->heat[y][x + dir] = 0;
				if (map->height > (y + dir) && (y + dir) >= 0 && filler->heat[y + dir][x] < PLAY)
					filler->heat[y + dir][x] = 0;
				x++;
			}
			filler->heat[y][x] = check_value(filler, map, x, y);
//			if (x - 1 >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y][x - 1] + 1;
//			if (x + 1 < map->width && filler->heat[y][x + 1] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y][x + 1] + 1;
//			if (y - 1 >= 0 && filler->heat[y - 1][x] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y - 1][x] + 1;
//			if (y + 1 < map->height && filler->heat[y + 1][x] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y + 1][x] + 1;
		}
	}
	return (filler);
}

/*
** This function creates the first half of the heatmap. It could be a universal
** function, but it would never fit the norm. So this was copied above for
** the reversing function that creates the second half.
*/

t_filler	*give_value_rev(t_filler *filler, t_block *map, int dir)
{
	int	y;
	int	x;

	y = map->height;
	while (--y >= 0)
	{
		x = map->width;
		while (--x >= 0)
		{
			if (filler->heat[y][x] == PLAY) // Skips the players positions.
				x--;
			if (filler->heat[y][x] == OPPO) // Marks zeroes around the opponent positions.
			{
				if (map->width > (x + dir) && (x + dir) >= 0 && filler->heat[y][x + dir] < PLAY)
					filler->heat[y][x + dir] = 0;
				if (map->height > (y + dir) && (y + dir) >= 0 && filler->heat[y + dir][x] < PLAY)
					filler->heat[y + dir][x] = 0;
				x--;
			}
			filler->heat[y][x] = check_value(filler, map, x, y);
//			if (x - 1 >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y][x - 1] + 1;
//			if (x + 1 < map->width && filler->heat[y][x + 1] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y][x + 1] + 1;
//			if (y - 1 >= 0 && filler->heat[y - 1][x] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y - 1][x] + 1;
//			if (y + 1 < map->height && filler->heat[y + 1][x] < filler->heat[y][x])
//				filler->heat[y][x] = filler->heat[y + 1][x] + 1;
			x--;
		}
	}
	return (filler);
}

/*
** Goes through the heatmap and inits the values to defaults. 200k for the enemy, 100k for the player and 1k
** for empty positions. With this, I can have conditions later, where I need to have one overlap with my own
** position -> aka. valid values are over 100k, but less than 200k. Then take the lowest value for the best
** position.
*/

 t_filler	*mark_players(t_filler *filler, t_block *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->cell[y][x] == filler->opponent || map->cell[y][x] == (filler->opponent + 32))
				filler->heat[y][x] = OPPO;
			else if (map->cell[y][x] == filler->player || map->cell[y][x] == (filler->player + 32))
				filler->heat[y][x] = PLAY;
			else
				filler->heat[y][x] = 1000;
		}
	}
	return (filler);
}

void		heatmapper(t_filler *filler, t_block *map, t_block *cell)
{
	filler = mark_players(filler, map);
	filler = give_value(filler, map, 1);
	filler = give_value_rev(filler, map, -1);
	solver(filler, map, cell);
}
