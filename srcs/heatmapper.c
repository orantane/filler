/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heatmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:16:18 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 19:38:30 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static int		check_zero(t_filler *filler, int x, int y)
{
	if ((x + 1) < filler->mapwidth && filler->heat[y][x + 1] == OPPO)
		return (0);
	if ((x - 1) >= 0 && filler->heat[y][x - 1] == OPPO)
		return (0);
	if ((y + 1) < filler->mapheight && filler->heat[y + 1][x] == OPPO)
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

static int		check_value(t_filler *filler, int x, int y)
{
	int		value;
	int		arr[5];
	int		i;

	i = -1;
	value = 1000;
	if (filler->heat[y][x] == PLAY)
		return (PLAY);
	if (filler->heat[y][x] == OPPO)
		return (OPPO);
	while (++i < 5)
		arr[i] = 1000;
	i = -1;
	if ((x + 1) < filler->mapwidth && filler->heat[y][x + 1] < filler->heat[y][x])
		arr[0] = filler->heat[y][x + 1] + 1;
	if ((x - 1) >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
		arr[1] = filler->heat[y][x - 1] + 1;
	if ((y + 1) < filler->mapheight && filler->heat[y + 1][x] < filler->heat[y][x])
		arr[2] = filler->heat[y + 1][x] + 1;
	if ((y - 1) >= 0 && filler->heat[y - 1][x] < filler->heat[y][x])
		arr[3] = filler->heat[y - 1][x] + 1;
	arr[4] = check_zero(filler, x, y);
	while (++i < 5)
	{
		if (arr[i] < value)
			value = arr[i];
	}
	return (value);
}

t_filler	*give_value(t_filler *filler)
{
	int	y;
	int	x;

	y = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		while (++x < filler->mapwidth)
		{
			if (filler->heat[y][x] == PLAY)
				x++;
			if (filler->heat[y][x] == OPPO)
				x++;
			filler->heat[y][x] = check_value(filler, x, y);
		}
	}
	return (filler);
}

/*
** This function creates the first half of the heatmap. It could be a universal
** function, but it would never fit the norm. So this was copied above for
** the reversing function that creates the second half.
*/

t_filler	*give_value_rev(t_filler *filler)
{
	int	y;
	int	x;

	y = filler->mapheight;
	while (--y >= 0)
	{
		x = filler->mapwidth;
		while (--x >= 0)
		{
			if (filler->heat[y][x] == PLAY) // Skips the players positions.
				x--;
			if (filler->heat[y][x] == OPPO) // Marks zeroes around the opponent positions.
				x--;
			filler->heat[y][x] = check_value(filler, x, y);
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

 t_filler	*mark_players(t_filler *filler)
{
	int	y;
	int	x;

	y = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		while (++x < filler->mapwidth)
		{
			if (filler->map[y][x] == filler->opponent || filler->map[y][x] == (filler->opponent + 32))
				filler->heat[y][x] = OPPO;
			else if (filler->map[y][x] == filler->player || filler->map[y][x] == (filler->player + 32))
				filler->heat[y][x] = PLAY;
			else
				filler->heat[y][x] = 1000;
		}
	}
	return (filler);
}

void		heatmapper(t_filler *filler)
{
	printf("Heatmapper map at start = %d, %d\n", filler->mapheight, filler->mapwidth);
	filler = mark_players(filler);
	printf("Heatmapper map at start = %d, %d\n", filler->mapheight, filler->mapwidth);
	filler = give_value(filler);
	printf("Heatmapper map at start = %d, %d\n", filler->mapheight, filler->mapwidth);
	filler = give_value_rev(filler);
	printf("Heatmapper map at start = %d, %d\n", filler->mapheight, filler->mapwidth);
	solver(filler);
}
