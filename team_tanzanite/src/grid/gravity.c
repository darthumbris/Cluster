/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gravity.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 20:06:05 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <move.h>

static void	collapse(char **board, t_coord origin)
{
	t_coord	up;
	t_coord	bubble;

	up.x = 1;
	up.y = 1;
	bubble.x = origin.x;
	bubble.y = origin.y;
	while (bubble.x < TOTAL_COLUMNS && bubble.y < TOTAL_COLUMNS
		&& !(board[bubble.x][bubble.y]))
	{
		bubble.x += up.x;
		bubble.y += up.y;
	}
	if (bubble.x >= TOTAL_COLUMNS || bubble.y >= TOTAL_COLUMNS)
		return ;
	board[origin.x][origin.y] = board[bubble.x][bubble.y];
	board[bubble.x][bubble.y] = 0;
}

static void	real_gravity(char **board)
{
	t_coord	coord;

	coord.y = 0;
	while (coord.y < TOTAL_COLUMNS)
	{
		coord.x = 0;
		while (coord.x < TOTAL_COLUMNS)
		{
			if (!(board[coord.x][coord.y]))
				collapse(board, coord);
			(coord.x)++;
		}
		(coord.y)++;
	}
}

void	copy_board(char **board_a, char **board_b)
{
	t_coord	coord;

	coord.y = 0;
	while (coord.y < TOTAL_COLUMNS)
	{
		coord.x = 0;
		while (coord.x < TOTAL_COLUMNS)
		{
			board_b[coord.x][coord.y] = board_a[coord.x][coord.y];
			(coord.x)++;
		}
		(coord.y)++;
	}
}

void	gravity(t_boards *boards)
{
	if (boards->which == A)
	{
		copy_board(boards->board_a, boards->board_b);
		real_gravity(boards->board_b);
		boards->which = B;
	}
	else
	{
		copy_board(boards->board_b, boards->board_a);
		real_gravity(boards->board_a);
		boards->which = A;
	}
}
