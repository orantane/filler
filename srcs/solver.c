/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:25:31 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 18:59:19 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		print_position(t_filler *filler)
{
	if (filler->val < PLAY || filler->val >= OPPO)
	{
		write(1, "0 0\n", 4);
		exit(1);
	}
	ft_putnbr(filler->y);
	write(1, " ", 1);
	ft_putnbr(filler->x);
	write(1, "\n", 1);
	free_cell(filler->map);
	free_cell(filler->cell);
}

void		place_cell(t_filler *filler, int y, int x)
{
	int		cy;
	int		cx;
	int		value;
	int		size;

	size = 0;
	cy = filler->off_y;
	value = 0;
	while (cy < filler->cellheight && (y + cy - filler->off_y) < filler->mapheight)
	{
		cx = filler->off_x;
		while ((x + cx - filler->off_x) < filler->mapwidth && cx < filler->cellwidth)
		{
			if (filler->cell[cy][cx] == '*' && size++ > -1)
				value = value + filler->heat[(y + cy - filler->off_y)][(x + cx - filler->off_x)];
			cx++;
		}
		cy++;
	}
	if (filler->size == size && value < OPPO && value > PLAY && value <= filler->val)
	{
		filler->val = value;
		filler->y = y - filler->off_y;
		filler->x = x - filler->off_x;
	}
}

/*
** This is where we go through the whole map and try to place the piece to the
** lowest value position. We can also add a function to check direction on cases
** where there are two values that are equal.
*/

void		get_low_value(t_filler *filler)
{
	int	y;
	int	x;

	y = -1;
	filler->y = -1;
	filler->x = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		while (++x < filler->mapwidth)
			place_cell(filler, y, x);
	}
}

void		set_offset(t_filler *filler, int y, int x)
{
	while (++y < filler->cellheight)
	{
		x = -1;
		while (++x < filler->cellwidth)
		{
			if (filler->cell[y][x] == '*')
			{
				if (x < filler->off_x)
					filler->off_x = x;
				if (y < filler->off_y)
					filler->off_y = y;
				filler->size++;
			}
		}
	}
}
