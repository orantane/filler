/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heatmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:16:18 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:15:34 by orantane         ###   ########.fr       */
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

static int		check_value(t_filler *filler, int x, int y, int i)
{
	int		value;
	int		arr[5];

	value = 1000;
	while (++i < 5)
		arr[i] = 1000;
	i = -1;
	if ((x + 1) < filler->mapwidth &&
			filler->heat[y][x + 1] < filler->heat[y][x])
		arr[0] = filler->heat[y][x + 1] + 1;
	if ((x - 1) >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
		arr[1] = filler->heat[y][x - 1] + 1;
	if ((y + 1) < filler->mapheight &&
			filler->heat[y + 1][x] < filler->heat[y][x])
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

void			give_value(t_filler *filler)
{
	int	y;
	int	x;
	int	i;

	i = -1;
	y = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		while (++x < filler->mapwidth)
		{
			if (filler->heat[y][x] == PLAY)
				continue ;
			if (filler->heat[y][x] == OPPO)
				continue ;
			filler->heat[y][x] = check_value(filler, x, y, i);
		}
	}
}

/*
** This function creates the second half of the heatmap. The function above
** does the same thing first, but in the opposite direction.
*/

void			give_value_rev(t_filler *filler)
{
	int	y;
	int	x;
	int	i;

	i = -1;
	y = filler->mapheight;
	while (--y >= 0)
	{
		x = filler->mapwidth;
		while (--x >= 0)
		{
			if (filler->heat[y][x] == PLAY)
				continue ;
			if (filler->heat[y][x] == OPPO)
				continue ;
			filler->heat[y][x] = check_value(filler, x, y, i);
		}
	}
}

/*
** Goes through the heatmap and inits the values to defaults. 200k for
** the opponent, 100k for the player and 1k for empty positions. With
** this, I can have conditions later, where I need to have one overlap
** with my own position -> aka. valid values are over 100k, but less
** than 200k. Then take the lowest value for the best position.
*/

void			heatmapper(t_filler *filler)
{
	int	y;
	int	x;

	y = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		while (++x < filler->mapwidth)
		{
			if (filler->map[y][x] == filler->opponent ||
				filler->map[y][x] == (filler->opponent + 32))
				filler->heat[y][x] = OPPO;
			else if (filler->map[y][x] == filler->player ||
					filler->map[y][x] == (filler->player + 32))
				filler->heat[y][x] = PLAY;
			else
				filler->heat[y][x] = 1000;
		}
	}
}
