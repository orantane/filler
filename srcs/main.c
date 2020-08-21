/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:28:44 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:50:20 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void		read_piece(t_filler *filler, char *line)
{
	int		y;
	char	*temp;

	y = -1;
	temp = line + 6;
	filler->cellheight = ft_atoi(temp);
	filler->cellwidth = ft_atoi(ft_strchr(temp, ' ') + 1);
	ft_strdel(&line);
	if (!(filler->cell =
		(char **)malloc((1 + filler->cellheight) * sizeof(char *))))
		exit(1);
	filler->cell[filler->cellheight] = NULL;
	while (++y < filler->cellheight)
	{
		if (y == (filler->cellheight - 1))
			get_next_line(0, &line, filler->cellwidth);
		else if (get_next_line(0, &line, 0) < 1)
			return ;
		if ((filler->cell[y] = ft_strdup(line)) == NULL)
			exit(1);
		ft_strdel(&line);
	}
}

void		read_map(t_filler *filler, char *line)
{
	int		y;

	y = 0;
	while (ft_strncmp(line, "000 ", 4) != 0)
	{
		ft_strdel(&line);
		if (get_next_line(0, &line, 0) < 1)
			return ;
	}
	if (!(filler->map =
		(char **)malloc((1 + filler->mapheight) * sizeof(char *))))
		return ;
	filler->map[filler->mapheight] = NULL;
	while (y < filler->mapheight && ft_strncmp(line, "Piece ", 6) != 0)
	{
		filler->map[y] = ft_strdup(line + 4);
		ft_strdel(&line);
		y++;
		if (get_next_line(0, &line, 0) != 1)
			exit(1);
	}
	read_piece(filler, line);
}

int			init_map(t_filler *filler, char *line)
{
	char	*temp;

	while (ft_strncmp(line, "Plateau ", 6) != 0)
	{
		get_next_line(0, &line, 0);
		if (ft_strncmp(line, "Plateau ", 6) == 0)
			break ;
		else
			ft_strdel(&line);
	}
	if (ft_strncmp(line, "Plateau ", 6) == 0)
	{
		temp = ft_strchr(line, ' ') + 1;
		filler->mapheight = ft_atoi(temp);
		filler->mapwidth = ft_atoi(ft_strchr(temp, ' ') + 1);
	}
	ft_strdel(&line);
	return (1);
}

void		set_players(t_filler *filler, char *line)
{
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
}

int			main(void)
{
	t_filler	filler;
	char		*line;

	ft_bzero(&filler, sizeof(t_filler));
	line = NULL;
	get_next_line(0, &line, 0);
	set_players(&filler, line);
	ft_strdel(&line);
	while (1)
	{
		init_struct(&filler);
		if (init_map(&filler, line) == 0)
			break ;
		read_map(&filler, line);
		heatmapper(&filler);
		give_value(&filler);
		set_offset(&filler, -1, -1);
		get_low_value(&filler);
		reset_heat(&filler);
		print_position(&filler);
		if (line)
			ft_strdel(&line);
	}
	return (0);
}
