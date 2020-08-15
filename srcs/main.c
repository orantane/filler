/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:28:44 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 17:00:45 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		free_cell(char **cell)
{
	int		i;

	i = -1;
	while (cell[++i])
		free(cell[i]);
	if (cell)
		free(cell);
}

void		read_piece(t_filler *filler, t_block *map, char *line)
{
	int		y;
	t_block	*cell;

	if (!(cell = (t_block *)malloc(sizeof(cell))))
		exit(1);
	y = -1;
	line = line + 6;
	cell->height = ft_atoi(line);
	cell->width = ft_atoi(ft_strchr(line, ' ') + 1);
	cell->cell = ft_memalloc((1 + cell->height) * sizeof(char *));
	cell->cell[cell->height] = NULL;
	while (++y < cell->height)
	{
		get_next_line(0, &line);
		cell->cell[y] = ft_strdup(line);
	}
	heatmapper(filler, map, cell);
}

void		read_map(t_filler *filler, t_block *map, char *line)
{
	int		y;

	y = 0;
	map->cell = ft_memalloc((1 + map->height) * sizeof(char *));
	map->cell[map->height] = NULL;
	while (ft_strncmp(line, "000 ", 4) != 0)
		get_next_line(0, &line);
	while (ft_strncmp(line, "Piece ", 6) != 0)
	{
		map->cell[y] = ft_strdup(line + 4);
		y++;
		if (get_next_line(0, &line) < 0)
			return ;
	}
	read_piece(filler, map, line);
}

void		init_map(t_filler *filler, char *line)
{
//	int		y;
	t_block	*map;

	if (!(map = (t_block *)malloc(sizeof(map))))
		exit(1);
//	y = -1;
	if (ft_strncmp(line, "Plateau ", 6) != 0)
		get_next_line(0, &line);
	if (ft_strncmp(line, "Plateau ", 6) == 0)
	{
		line = ft_strchr(line, ' ') + 1;
		map->height = ft_atoi(line);
		map->width = ft_atoi(ft_strchr(line, ' ') + 1);
	}
//	while (++y < map->height)
//	{
//		if (!(filler->heat[y] = (int *)malloc(sizeof(int) * map->width)))
//			return ;
//	}
	read_map(filler, map, line);
}

int			main(void)
{
	t_filler	*filler;
	char		*line;

	if (!(filler = (t_filler *)malloc(sizeof(filler))))
		return (0);
	line = NULL;
	if (get_next_line(0, &line) < 0)
		return (0);
	if (line && ft_strncmp(line, "$$$ exec p", 9) == 0
		&& (line[10] == '1' || line[10] == '2'))
	{
		if (line[10] == '1')
		{
			filler->player = 'O';
			filler->opponent = 'X';
		}
		else
		{
			filler->player = 'X';
			filler->opponent = 'O';
		}
	}
	init_map(filler, line);
	return (1);
}
