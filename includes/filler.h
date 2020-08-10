/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:36 by orantane          #+#    #+#             */
/*   Updated: 2020/08/10 16:36:40 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# include "../libft/libft.h"
# include <stdio.h> //remove this before turning in!

/*
** Struct for all coordinates.
*/

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/*
** Struct for the map and incoming blocks.
*/

typedef struct	s_block
{
	int			width;
	int			height;
	int			size;
	char		**cell;
}				t_block;

/*
** Megastruct to hold all the data. The "dir" array should be used to store the direction of the expansion.
** There needs to be a calculation to create a heatmap of the opponent and an overall coverage of the map.
** With this data, we need to create a direction to expand to. 1 for top left, 2 for top, 3 for top right
** and so on. There should also be a small function to check the distance to the enemy, so that if there
** is enough time the function should try to keep a small distance in order to be able to place the blocks.
*/

typedef struct	s_filler
{
	t_coord		pos;
	t_block		map;
	t_block		cell;
	int			**heat;
	char		player;
	char		opponent;
}				t_filler;

int			main(void);
void		init_map(t_filler *filler);
void		read_map(t_filler *filler);
void		read_piece(t_filler *filler, char *line);

#endif
