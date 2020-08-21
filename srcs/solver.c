/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:25:31 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:34:05 by orantane         ###   ########.fr       */
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
	free_cell(filler->map, filler->mapheight);
	free_cell(filler->cell, filler->cellheight);
}

void		place_cell(t_filler *filler, int y, int x)
{
	int		a;
	int		b;
	int		v;
	int		size;

	size = 0;
	a = filler->oy;
	v = 0;
	while (a < filler->cellheight && y + a - filler->oy < filler->mapheight)
	{
		b = filler->ox;
		while (x + b - filler->ox < filler->mapwidth && b < filler->cellwidth)
		{
			if (filler->cell[a][b] == '*' && size++ > -1)
				v = v + filler->heat[y + a - filler->oy][x + b - filler->ox];
			b++;
		}
		a++;
	}
	if (filler->size == size && v < OPPO && v > PLAY && v <= filler->val)
	{
		filler->val = v;
		filler->y = y - filler->oy;
		filler->x = x - filler->ox;
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
				if (x < filler->ox)
					filler->ox = x;
				if (y < filler->oy)
					filler->oy = y;
				filler->size++;
			}
		}
	}
}
