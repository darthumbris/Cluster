/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   column.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 20:01:34 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/07 20:01:35 by rrinia        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <move.h>

static int	real_column_move(char **board, int column_number, int colour)
{
	if (board[translate(column_number).x][translate(column_number).y])
		return (1);
	board[translate(column_number).x][translate(column_number).y] = colour;
	return (0);
}

int	column_move(t_boards *boards, int column_number, int colour)
{
	if (boards->which == A)
		return (real_column_move(boards->board_a, column_number, colour));
	return (real_column_move(boards->board_b, column_number, colour));
}
