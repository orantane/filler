/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:36 by orantane          #+#    #+#             */
/*   Updated: 2020/08/15 20:52:51 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define PLAY 100000
# define OPPO 200000
# define OFFS 10000

# include "../libft/libft.h"
# include <stdio.h> //remove this before turning in!

/*
** Megastruct to hold all the data. The "dir" array should be used to store the direction of the expansion.
** There needs to be a calculation to create a heatmap of the opponent and an overall coverage of the map.
** With this data, we need to create a direction to expand to. 1 for top left, 2 for top, 3 for top right
** and so on. There should also be a small function to check the distance to the enemy, so that if there
** is enough time the function should try to keep a small distance in order to be able to place the blocks.
*/

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
	int			off_y;
	int			off_x;
	int			over_y;
	int			over_x;
	char		player;
	char		opponent;
	char		**map;
	char		**cell;
	int			heat[200][200];
}				t_filler;

int			main(void);
void		init_map(t_filler *filler, char *line);
void		read_map(t_filler *filler, char *line);
void		read_piece(t_filler *filler, char *line);
void		free_cell(char **cell);
void		heatmapper(t_filler *filler);
void		mark_players(t_filler *filler);
void		give_value(t_filler *filler);
void		give_value_rev(t_filler *filler);
void		solver(t_filler *filler);

#endif
