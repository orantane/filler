/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:36 by orantane          #+#    #+#             */
/*   Updated: 2020/07/30 17:43:59 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# include "../libft/libft.h"

/*
** Struct for all coordinates.
*/

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/*
** Struct for the players and the starting coordinates.
*/

typedef struct	s_player
{
	int			id;
	t_coord		start;
}				t_player;

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
	t_player	player;
	t_player	opponent;
	t_coord		target;
	t_block		map;
	t_block		cell;
	int			dir[8];
}				t_filler;

int			main(int argc, char **argv);

#endif
