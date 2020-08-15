/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:25:31 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 16:56:16 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static void		print_position(t_filler *filler)
{
	ft_putnbr(filler->x);
	write(1, " ", 1);
	ft_putnbr(filler->y);
	write(1, "\n", 1);
}

static t_filler	*place_cell(t_filler *filler, t_block *map, t_block *cell, int y, int x)
{
	int		cy;
	int		cx;
	int		value;
	int		size;

	size = 0;
	cy = filler->off_y;
	value = 0;
	while (cell->cell[cy] && (y + cy - filler->off_y) < map->height &&
			(y + cy - filler->off_y) > -1)//Checks that the block doesn't go out of the map on y-axis.
	{
		cx = filler->off_x;
		while(cell->cell[cy][cx] && (x + cx - filler->off_x) < map->width &&
				(x + cx - filler->off_x) > -1)// Block doesn't go out of the map on x-axis.
		{
			if (cell->cell[cy][cx] == '*')
			{
				value = value + filler->heat[(y + cy - filler->off_y)][(x + cx - filler->off_x)];
				size++;
			}
			cx++;
		}
		cy++;
	}
	if (filler->size == size && value < OPPO && value > PLAY && value < filler->val)
	{
		filler->val = value;
		filler->y = y - filler->off_y;
		filler->x = x - filler->off_x;
	}
	return (filler);
}

/*
** This is where we go through the whole map and try to place the piece to the
** lowest value position. We can also add a function to check direction on cases
** where there are two values that are equal.
*/

static t_filler	*get_low_value(t_filler *filler, t_block *map, t_block *cell)
{
	int	y;
	int	x;

	y = -1;
	filler->y = -1;
	filler->x = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			filler = place_cell(filler, map,cell, y, x);
		}
	}
	return (filler);
}

static t_filler	*set_offset(t_filler *filler, int y, int x, t_block *cell)
{
	filler->size = 0;
	while (++y < cell->height)
	{
		x = -1;
		while (++x < cell->width)
		{
			if (cell->cell[y][x] == '*')
			{
				if (x < filler->off_x)
					filler->off_x = x;
				if (y < filler->off_y)
					filler->off_y = y;
				if (y > filler->over_y)
					filler->over_y = y;
				if (x > filler->over_x)
					filler->over_x = x;
				filler->size++;
			}
		}
	}
	return (filler);
}

void			solver(t_filler *filler, t_block *map, t_block *cell)
{
	int		x;
	int		y;

	filler->off_y = OFFS;
	filler->off_x = OFFS;
	filler->over_y = 0;
	filler->over_x = 0;
	filler->val = 200000;
	x = -1;
	y = -1;
	filler = set_offset(filler, y, x, cell);
	filler = get_low_value(filler, map, cell);
	while (++y < 14)
	{
		x = -1;
		while (++x < 30)
			printf("%d\t", filler->heat[y][x]);
		printf("\n");
	}
	if (filler->val < PLAY || filler->val >= OPPO)
		exit(1);
	print_position(filler);
}
