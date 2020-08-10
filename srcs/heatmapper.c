/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heatmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 14:16:18 by orantane          #+#    #+#             */
/*   Updated: 2020/08/10 16:52:26 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

t_filler	*give_value(t_filler *filler, int x, int y, int dir)
{
	int		opponent;
	int		player;

	opponent = 200000;
	player = 100000;
	while (++y < filler->map.height)
	{
		x = -1;
		while (++x < filler->map.width)
		{
			if (filler->heat[y][x] == player) // Skips the players positions.
				continue ;
			if (filler->heat[y][x] == opponent) // Marks zeroes around the opponent positions.
			{
				if (filler->map.width > (x + dir) && (x + dir) >= 0)
					filler->heat[y][x + dir] = 0;
				if (filler->map.height > (y + dir) && (y + dir) >= 0)
					filler->heat[y + dir][x] = 0;
			}
			if (x - 1 >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y][x - 1] + 1;
			if (x + 1 <= filler->map.width && filler->heat[y][x - 1] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y][x + 1] + 1;
			if (y - 1 >= 0 && filler->heat[y - 1][x] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y - 1][x] + 1;
			if (y + 1 <= filler->map.height && filler->heat[y + 1][x] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y + 1][x] + 1;
		}
	}
	return (filler);
}

/*
** This function creates the first half of the heatmap. It could be a universal
** function, but it would never fit the norm. So this was copied above for
** the reversing function that creates the second half.
*/

t_filler	*give_value_rev(t_filler *filler, int x, int y, int dir)
{
	int		opponent;
	int		player;

	opponent = 200000;
	player = 100000;
	while (y >= 0)
	{
		while (x >= 0)
		{
			if (filler->heat[y][x] == player) // Skips the players positions.
				continue ;
			if (filler->heat[y][x] == opponent) // Marks zeroes around the opponent positions.
			{
				if (filler->map.width > (x + dir) && (x + dir) >= 0)
					filler->heat[y][x + dir] = 0;
				if (filler->map.height > (y + dir) && (y + dir) >= 0)
					filler->heat[y + dir][x] = 0;
			}// Under this: Checks positions around the current position, to see what is the correct value.
			// This can be copied to another function so that it serves as a universal function.
			if (x - 1 >= 0 && filler->heat[y][x - 1] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y][x - 1] + 1;
			if (x + 1 <= filler->map.width && filler->heat[y][x - 1] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y][x + 1] + 1;
			if (y - 1 >= 0 && filler->heat[y - 1][x] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y - 1][x] + 1;
			if (y + 1 <= filler->map.height && filler->heat[y + 1][x] < filler->heat[y][x])
				filler->heat[y][x] = filler->heat[y + 1][x] + 1;
			x--;
		}
		x = filler->map.width;
		y--;
	}
	return (filler);
}

/*
** Goes through the heatmap and inits the values to defaults. 200k for the enemy, 100k for the player and 1k
** for empty positions. With this, I can have conditions later, where I need to have one overlap with my own
** position -> aka. valid values are over 100k, but less than 200k. Then take the lowest value for the best
** position.
*/

t_filler	*mark_players(t_filler *filler, int x, int y)
{
	int		opponent;
	int		player;

	opponent = 200000;
	player = 100000;
	while (filler->map.cell[++y])
	{
		while (filler->map.cell[y][++x])
		{
			if (filler->map.cell[y][x] == filler->opponent)
				filler->heat[y][x] = opponent;
			else if (filler->map.cell[y][x] == filler->player)
				filler->heat[y][x] = player;
			else
				filler->heat[y][x] = 1000;
		}
		x = -1;
	}
	return (filler);
}

void		heatmapper(t_filler *filler)
{
	int		y;
	int		x;

	y = -1;
	x = -1;
	filler = mark_players(filler, y, x);
	filler = give_value(filler, y, x, 1);
	filler = give_value_rev(filler, filler->map.height, filler->map.width, -1);
	solver(filler);
}
