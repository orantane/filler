/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 20:07:45 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:25:13 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		reset_heat(t_filler *filler)
{
	int		y;
	int		x;

	y = -1;
	while (++y < 200)
	{
		x = -1;
		while (++x < 200)
			filler->heat[y][x] = 1000;
	}
}

void		free_cell(char **cell, int len)
{
	int		i;

	i = -1;
	while (++i <= len)
		free(cell[i]);
	if (cell)
		free(cell);
}

void		init_struct(t_filler *filler)
{
	filler->mapheight = 0;
	filler->mapwidth = 0;
	filler->cellwidth = 0;
	filler->cellheight = 0;
	filler->x = 0;
	filler->y = 0;
	filler->val = OPPO;
	filler->oy = OPPO;
	filler->ox = OPPO;
	filler->size = 0;
	filler->map = NULL;
	filler->cell = NULL;
}
