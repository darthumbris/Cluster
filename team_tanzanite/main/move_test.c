/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 18:18:14 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/07 18:18:15 by rrinia        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <move.h>
#include <stdlib.h>

/*
 * Test made for side-length and win length 3.
 * Creates a situation where two "winning" lines are created at once, then adds
 * a game piece to one of them, causing a unique winning line to exist.
 *
 * A demonstration of the mirrored case follows, then a more trivial case is
 * presented that simply drops multiple numbers on the same column without any
 * counterplay.
 *
 * NEW: Code now accepts a win if all (non unique) longest lines consist of
 * pieces from the same player. An example has been added.
 */

int	main(void)
{
	t_boards	*boards;
	t_parse		my_move;

	boards = initialize();
	if (!boards)
		return (1);
	visualize_text(boards);
	my_move.input = column;
	my_move.data.column_data.column = 1;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);

	my_move.data.column_data.column = 1;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	visualize_text(boards);

	my_move.input = rotation;
	my_move.data.rotation = 1;
	move(boards, &my_move);
	visualize_text(boards);	

	my_move.input = column;
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);

	visualize_text(boards);	
	clear_boards(boards);

	boards = initialize();
	if (!boards)
		return (1);

	my_move.input = column;
	my_move.data.column_data.column = -1;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);

	my_move.data.column_data.column = -1;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);
	visualize_text(boards);

	my_move.input = rotation;
	my_move.data.rotation = 5;
	move(boards, &my_move);
	visualize_text(boards);	

	my_move.input = column;
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 2;
	move(boards, &my_move);

	visualize_text(boards);	
	clear_boards(boards);

	boards = initialize();
	if (!boards)
		return (1);
	my_move.input = column;
	my_move.data.column_data.column = 0;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	move(boards, &my_move);
	move(boards, &my_move);
	visualize_text(boards);	
	clear_boards(boards);

	boards = initialize();
	if (!boards)
		return (1);
	visualize_text(boards);
	my_move.input = column;
	my_move.data.column_data.column = 1;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 1;
	move(boards, &my_move);

	my_move.data.column_data.column = 1;
	my_move.data.column_data.colour = 3;
	move(boards, &my_move);
	my_move.data.column_data.column = 2;
	my_move.data.column_data.colour = 3;
	move(boards, &my_move);
	my_move.data.column_data.column = -2;
	my_move.data.column_data.colour = 3;
	move(boards, &my_move);
	visualize_text(boards);

	my_move.input = rotation;
	my_move.data.rotation = 1;
	move(boards, &my_move);
	visualize_text(boards);	

	clear_boards(boards);
	return (0);
}
