/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:23:05 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <move.h>

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static t_directions	xy_to_hex(t_coord coord)
{
	t_directions	out;

	out.up[0] = min(coord.x, coord.y);
	out.left[0] = coord.x - out.up[0];
	out.right[0] = coord.y - out.up[0];
	return (out);
}

// I feel like this is a little cleaner.
static void	translate_coords(t_coord coord_a, t_coord *coord_b, int steps)
{
	t_directions	dirs;

	if (steps == 1)
		dirs = (t_directions){{g_options.board_width - 1, 0}, {1, 1}, {-1, 0}, {0, 1}};
	else if (steps == 2)
		dirs = (t_directions){{TOTAL_COLUMNS - 1, g_options.board_width - 1}, {0, 1}, {-1, -1}, {-1, 0}};
	else if (steps == 3)
		dirs = (t_directions){{TOTAL_COLUMNS - 1, TOTAL_COLUMNS - 1}, {-1, 0}, {0, -1}, {-1, -1}};
	else if (steps == 4)
		dirs = (t_directions){{g_options.board_width - 1, TOTAL_COLUMNS - 1}, {-1, -1}, {1, 0}, {0, -1}};
	else if (steps == 5)
		dirs = (t_directions){{0, g_options.board_width - 1}, {0, -1}, {1, 1}, {1, 0}};
	// Initialize here to silence the compiler a bit.
	else
		dirs = (t_directions){{g_options.board_width - 1, 0}, {1, 1}, {-1, 0}, {0, 1}};
	coord_b->x = (dirs.origin[0] + (xy_to_hex(coord_a).up[0] * dirs.up[0])
			+ (xy_to_hex(coord_a).left[0] * dirs.left[0])
			+ (xy_to_hex(coord_a).right[0] * dirs.right[0]));
	coord_b->y = (dirs.origin[1] + (xy_to_hex(coord_a).up[0] * dirs.up[1])
			+ (xy_to_hex(coord_a).left[0] * dirs.left[1])
			+ (xy_to_hex(coord_a).right[0] * dirs.right[1]));
}


/*static void	translate_coords(t_coord coord_a, t_coord *coord_b, int steps)
{
	t_directions	dirs;

	if (steps == 1)
	{
		dirs.origin[0] = g_options.board_width - 1;
		dirs.origin[1] = 0;
		dirs.left[0] = 1;
		dirs.left[1] = 1;
		dirs.right[0] = -1;
		dirs.right[1] = 0;
		dirs.up[0] = 0;
		dirs.up[1] = 1;
	}
	else if (steps == 2)
	{
		dirs.origin[0] = TOTAL_COLUMNS - 1;
		dirs.origin[1] = g_options.board_width - 1;
		dirs.left[0] = 0;
		dirs.left[1] = 1;
		dirs.right[0] = -1;
		dirs.right[1] = -1;
		dirs.up[0] = -1;
		dirs.up[1] = 0;
	}
	else if (steps == 3)
	{
		dirs.origin[0] = TOTAL_COLUMNS - 1;
		dirs.origin[1] = TOTAL_COLUMNS - 1;
		dirs.left[0] = -1;
		dirs.left[1] = 0;
		dirs.right[0] = 0;
		dirs.right[1] = -1;
		dirs.up[0] = -1;
		dirs.up[1] = -1;
	}
	else if (steps == 4)
	{
		dirs.origin[0] = g_options.board_width - 1;
		dirs.origin[1] = TOTAL_COLUMNS - 1;
		dirs.left[0] = -1;
		dirs.left[1] = -1;
		dirs.right[0] = 1;
		dirs.right[1] = 0;
		dirs.up[0] = 0;
		dirs.up[1] = -1;
	}
	else if (steps == 5)
	{
		dirs.origin[0] = 0;
		dirs.origin[1] = g_options.board_width - 1;
		dirs.left[0] = 0;
		dirs.left[1] = -1;
		dirs.right[0] = 1;
		dirs.right[1] = 1;
		dirs.up[0] = 1;
		dirs.up[1] = 0;
	}
	coord_b->x = (dirs.origin[0] + (xy_to_hex(coord_a).up[0] * dirs.up[0])
			+ (xy_to_hex(coord_a).left[0] * dirs.left[0])
			+ (xy_to_hex(coord_a).right[0] * dirs.right[0]));
	coord_b->y = (dirs.origin[1] + (xy_to_hex(coord_a).up[0] * dirs.up[1])
			+ (xy_to_hex(coord_a).left[0] * dirs.left[1])
			+ (xy_to_hex(coord_a).right[0] * dirs.right[1]));
}*/

static void	real_rotate_move(char **board_a, char **board_b, int steps)
{
	t_coord	coord_a;
	t_coord	coord_b;

	coord_a.x = 0;
	while (coord_a.x < TOTAL_COLUMNS)
	{
		coord_a.y = 0;
		while (coord_a.y < TOTAL_COLUMNS)
		{
			translate_coords(coord_a, &coord_b, steps);
			if (coord_b.x >= 0 && coord_b.y >= 0 && coord_b.x < TOTAL_COLUMNS
				&& coord_b.y < TOTAL_COLUMNS)
				board_b[coord_b.x][coord_b.y] = board_a[coord_a.x][coord_a.y];
			(coord_a.y)++;
		}
		(coord_a.x)++;
	}
}

void	rotate_move(t_boards *boards, int steps)
{
	if (boards->which == A)
	{
		real_rotate_move(boards->board_a, boards->board_b, steps);
		boards->which = B;
	}
	else
	{
		real_rotate_move(boards->board_b, boards->board_a, steps);
		boards->which = A;
	}
}
