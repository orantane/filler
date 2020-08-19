/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:28:44 by orantane          #+#    #+#             */
/*   Updated: 2020/08/19 17:58:01 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		free_cell(char **cell)
{
	int		i;

	i = -1;
	while (cell[++i] != NULL)
		free(cell[i]);
	if (cell != NULL)
		free(cell);
}

void		init_struct(t_filler *filler)
{
	filler->cellwidth = 0;
	filler->cellheight = 0;
	filler->x = 0;
	filler->y = 0;
	filler->val = OPPO;
	filler->off_y = OPPO;
	filler->off_x = OPPO;
	filler->size = 0;
	filler->map = NULL;
	filler->cell = NULL;
}

void		read_piece(t_filler *filler, char *line)
{
	int		y;

	y = -1;
	line = line + 6;
	filler->cellheight = ft_atoi(line);
	filler->cellwidth = ft_atoi(ft_strchr(line, ' ') + 1);
	if (!(filler->cell =
		(char **)malloc((1 + filler->cellheight) * sizeof(char *))))
	{
		write(1, "error\n", 6);
		exit(1);
	}
	filler->cell[filler->cellheight] = NULL;
	while (++y < filler->cellheight)
	{
		get_next_line(0, &line);
		if ((filler->cell[y] = ft_strdup(line)) == NULL)
			return ;
	}
	filler->inited = 1;
	free(line);
	heatmapper(filler);
}

void		read_map(t_filler *filler, char *line)
{
	int		y;

	y = 0;
	init_struct(filler);
	if (!(filler->map =
		(char **)malloc((1 + filler->mapheight) * sizeof(char *))))
		return ;
	filler->map[filler->mapheight] = NULL;
	while (ft_strncmp(line, "000 ", 4) != 0)
	{
		if (get_next_line(0, &line) < 1)
			break ;
	}
	while (y < filler->mapheight)
	{
		filler->map[y] = ft_strdup(line + 4);
		y++;
		get_next_line(0, &line);
	}
	read_piece(filler, line);
}

void		init_map(t_filler *filler, char *line)
{
	filler->mapheight = 0;
	filler->mapwidth = 0;
	if (ft_strncmp(line, "Plateau ", 6) != 0)
		get_next_line(0, &line);
	if (ft_strncmp(line, "Plateau ", 6) == 0)
	{
		line = ft_strchr(line, ' ') + 1;
		filler->mapheight = ft_atoi(line);
		filler->mapwidth = ft_atoi(ft_strchr(line, ' ') + 1);
	}
	read_map(filler, line);
}

int			main(void)
{
	t_filler	filler;
	char		*line;

	line = NULL;
	if (get_next_line(0, &line) < 0)
		exit(1);
	if (line && ft_strncmp(line, "$$$ exec p", 9) == 0
		&& (line[10] == '1' || line[10] == '2'))
	{
		if (line[10] == '1')
		{
			filler.player = 'O';
			filler.opponent = 'X';
		}
		else
		{
			filler.player = 'X';
			filler.opponent = 'O';
		}
	}
	init_map(&filler, line);
	return (1);
}
