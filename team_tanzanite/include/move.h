/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:38:40 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 19:48:18 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATE_H
# define ROTATE_H

# include <initialize.h>
# include <parsing.h>
# include <cluster.h>

typedef struct s_directions
{
	int	origin[2];
	int	left[2];
	int	right[2];
	int	up[2];
}	t_directions;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_long_one
{
	int		length;
	t_coord	where[2];
}	t_long_one;

void	move(t_boards *boards, t_parse *move);

void	visualize_text(t_cluster *cluster);
void	real_visualize_text(char **board, t_player *players);
int		min(int a, int b);
t_coord	translate(int column_number);
void	rotate_move(t_boards *boards, int steps);
int		column_move(t_boards *boards, int column_number, int colour);
void	gravity(t_boards *boards);
int		winner_test(t_boards *boards);
void	copy_board(char **board_a, char **board_b);

#endif
