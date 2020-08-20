/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:28:44 by orantane          #+#    #+#             */
/*   Updated: 2020/08/20 22:55:48 by orantane         ###   ########.fr       */
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
	filler->mapheight = 0;
	filler->mapwidth = 0;
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

void		read_piece(t_filler *filler, char *line, int fd)
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
		if (y == (filler->cellheight -1))
		{
			get_next_line(0, &line, filler->cellwidth);
		}
		else if (get_next_line(0, &line, 0) < 1)
			return ;
		if ((filler->cell[y] = ft_strdup(line)) == NULL)
			exit(1);
		ft_strdel(&line);
	}
	heatmapper(filler);
	give_value(filler);
	give_value_rev(filler);
	y = -1;
	int x;
	while (++y < 15)
	{
		x = -1;
		while (++x < 17)
		{
			ft_putnbr_fd(filler->heat[y][x], fd);
			ft_putchar_fd('\t', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
	ft_putchar_fd('\n', fd);
	set_offset(filler, -1, -1);
	get_low_value(filler);
	print_position(filler);
	free_cell(filler->map);
	free_cell(filler->cell);
	reset_heat(filler);
}

void		read_map(t_filler *filler, char *line, int fd)
{
	int		y;

	y = 0;
	while (ft_strncmp(line, "000 ", 4) != 0)
	{
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
			exit (1);
	}
	read_piece(filler, line, fd);
}

int			init_map(t_filler *filler, char *line)
{
	while (ft_strncmp(line, "Plateau ", 6) != 0)
	{
		if (get_next_line(0, &line, 0) < 1)
			return (0);
	}
	if (ft_strncmp(line, "Plateau ", 6) == 0)
	{
		line = ft_strchr(line, ' ') + 1;
		filler->mapheight = ft_atoi(line);
		filler->mapwidth = ft_atoi(ft_strchr(line, ' ') + 1);
	}
	else
		return (0);
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
	int			fd;
	int			count;

	count = 0;
	fd = open("/Users/orantane/Desktop/Projects/filler/github/d.txt", O_RDWR);
	ft_bzero(&filler, sizeof(t_filler));
	line = NULL;
	get_next_line(0, &line, 0);
	set_players(&filler, line);
	ft_strdel(&line);
	while (1)
	{
		get_next_line(0, &line, 0);
		init_struct(&filler);
		if (init_map(&filler, line) == 0)
			break ;
		read_map(&filler, line, fd);
		if (line)
			ft_strdel(&line);
	}
	return (0);
}
