/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   winner_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By:                                              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 00:04:04 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/11 10:27:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include <stdlib.h>
#include <stdio.h>

static int	traverse(char **board, t_coord coord, t_coord delta)
{
	char	colour;
	int		count;

	colour = board[coord.x][coord.y];
	if (!colour)
		return (0);
	count = 0;
	while (coord.x >= 0 && coord.y >= 0 && coord.x < TOTAL_COLUMNS
		&& coord.y < TOTAL_COLUMNS && board[coord.x][coord.y] == colour)
	{
		coord.x += delta.x;
		coord.y += delta.y;
		count++;
	}
	return (count);
}

static void	check_if_better(char **board, t_coord coord, t_coord delta,
			t_long_one *best)
{
	if (traverse(board, coord, delta) > best->length)
	{
		best->length = traverse(board, coord, delta);
		best->where[0].x = coord.x;
		best->where[0].y = coord.y;
		best->where[1].x = delta.x;
		best->where[1].y = delta.y;
	}
}

static t_long_one	*real_winner_test_inner(char **board, int parity)
{
	t_coord		coord;
	t_coord		delta;
	t_long_one	*best;

	best = (t_long_one *)calloc(1, sizeof(t_long_one));
	if (!best)
		return (NULL);
	coord.y = 0;
	while (coord.y < TOTAL_COLUMNS)
	{
		coord.x = 0;
		while (coord.x < TOTAL_COLUMNS)
		{
			if ((board[coord.x][coord.y] & 1) == parity)
			{
				delta.x = 1;
				delta.y = 0;
				check_if_better(board, coord, delta, best);
				delta.y = 1;
				check_if_better(board, coord, delta, best);
				delta.x = 0;
				check_if_better(board, coord, delta, best);
			}
			(coord.x)++;
		}
		(coord.y)++;
	}
	return (best);
}

static int	real_winner_test(char **board)
{
	t_long_one	*best_p1;
	t_long_one	*best_p2;
	int			winner;

	best_p1 = real_winner_test_inner(board, 1);
	if (!best_p1)
		return (-1);
	best_p2 = real_winner_test_inner(board, 0);
	if (!best_p2)
		return (-1);
	if (best_p1->length >= g_options.in_a_row && best_p1->length > best_p2->length)
		winner = board[best_p1->where[0].x][best_p1->where[0].y];
	else if (best_p2->length >= g_options.in_a_row && best_p2->length > best_p1->length)
		winner = board[best_p2->where[0].x][best_p2->where[0].y];
	else
		winner = 0;
	free(best_p1);
	free(best_p2);
	return (winner);
}

int	winner_test(t_boards *boards)
{
	if (boards->which == A)
		return (real_winner_test(boards->board_a));
	return (real_winner_test(boards->board_b));
}
