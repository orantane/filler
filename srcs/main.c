/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:28:44 by orantane          #+#    #+#             */
/*   Updated: 2020/08/10 16:51:32 by orantane         ###   ########.fr       */
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

void		read_piece(t_filler *filler, char *line)
{
	int		y;

	y = -1;
	line = line + 6;
	filler->cell.height = ft_atoi(line);
	filler->cell.width = ft_atoi(ft_strchr(line, ' ') + 1);
	if (filler->cell.cell)
		free_cell(filler->cell.cell);
	filler->cell.cell = ft_memalloc(filler->cell.height * sizeof(char *));
	while (++y < filler->cell.height)
	{
		get_next_line(0, &line);
		filler->cell.cell[y] = ft_strdup(line);
	}
	heatmapper(filler);
}

void		read_map(t_filler *filler)
{
	int		y;

	y = 0;
	if (filler->map.cell)
		free_cell(filler->map.cell);
	filler->map.cell = ft_memalloc(filler->map.height * sizeof(char *));
	while (ft_strncmp(line, "000 ", 4) != 0)
		get_next_line(0, &line);
	while (ft_strncmp(line, "Piece ", 5) != 0)
	{
		filler->map.cell[y] = ft_strdup(line + 4);
		y++;
		if (get_next_line(0, &line) < 0)
			return ;
	}
	read_piece(filler, line);
}

void		init_map(t_filler *filler)
{
	char	*line;
	int		y;


	y = -1;
	line = NULL;
	if (get_next_line(0, &line) < 0)
		return ;
	if (ft_strncmp(line, "Plateau ", 6) == 0)
	{
		line = ft_strchr(line, ' ') + 1;
		filler->map.height = ft_atoi(line);
		filler->map.width = ft_atoi(ft_strchr(line, ' ') + 1);
	}
	filler->heat = ft_memalloc(filler->cell.height * sizeof(int *));
	while (++y < filler->map.height)
	{
		if (!(filler->heat[y] = (int *)malloc(sizeof(int) * filler->map.width)))
			return ;
	}
	read_map(filler);
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
		ft_strdel(&line);
	}
	init_map(filler);
	return (1);
}
