/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:36 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:47:48 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define PLAY 100000
# define OPPO 200000
# define OFFS 10000

# include "../libft/libft.h"

typedef struct	s_filler
{
	int			mapwidth;
	int			mapheight;
	int			cellwidth;
	int			cellheight;
	int			x;
	int			y;
	int			val;
	int			size;
	int			oy;
	int			ox;
	char		player;
	char		opponent;
	char		**map;
	char		**cell;
	int			heat[200][200];
}				t_filler;

int			main(void);
void		init_struct(t_filler *filler);
void		set_players(t_filler *filler, char *line);
int			init_map(t_filler *filler, char *line);
void		read_map(t_filler *filler, char *line);
void		read_piece(t_filler *filler, char *line);
void		free_cell(char **cell, int len);
void		reset_heat(t_filler *filler);
void		heatmapper(t_filler *filler);
void		give_value(t_filler *filler);
void		give_value_rev(t_filler *filler);
void		set_offset(t_filler *filler, int y, int x);
void		get_low_value(t_filler *filler);
void		print_position(t_filler *filler);

#endif
