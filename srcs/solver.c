/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 15:25:31 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 19:46:24 by orantane         ###   ########.fr       */
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

static t_filler	*place_cell(t_filler *filler, int y, int x)
{
	int		cy;
	int		cx;
	int		value;
	int		size;

	size = 0;
	cy = filler->off_y;
	value = 0;
	while ((y + cy - filler->off_y) < filler->mapheight &&
			(y + cy - filler->off_y) > -1 && cy < filler->cellheight)
	{
		cx = filler->off_x;
		while((x + cx - filler->off_x) < filler->mapwidth &&
				(x + cx - filler->off_x) > -1 && cx < filler->cellwidth)
		{
			if (filler->cell[cy][cx] == '*')
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

static t_filler	*get_low_value(t_filler *filler)
{
	int	y;
	int	x;

	y = -1;
	filler->y = -1;
	filler->x = -1;
	while (++y < filler->mapheight)
	{
		x = -1;
		printf("y: ");
		while (++x < filler->mapwidth)
		{
			filler = place_cell(filler, y, x);
			printf("x ");
		}
		printf("\n");
	}
	return (filler);
}

static t_filler	*set_offset(t_filler *filler, int y, int x)
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

void			solver(t_filler *filler)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	filler = set_offset(filler, y, x);
	printf("map before offset = %d, %d\n", filler->mapheight, filler->mapwidth);
	filler = get_low_value(filler);
	printf("map before offset = %d, %d\n", filler->mapheight, filler->mapwidth);
//	while (++y < 14)
//	{
//		x = -1;
//		while (++x < 30)
//			printf("%d\t", filler->heat[y][x]);
//		printf("\n");
//	}
	if (filler->val < PLAY || filler->val >= OPPO)
		exit(1);
	print_position(filler);
}
