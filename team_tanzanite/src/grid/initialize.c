/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:56:08 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <initialize.h>
#include <stdlib.h>

void	clear_board(char **board)
{
	int	i;

	i = 0;
	while (i < TOTAL_COLUMNS)
	{
		free(board[i]);
		i++;
	}
	free(board);
}

void	clear_boards(t_boards *boards)
{
	clear_board(boards->board_a);
	clear_board(boards->board_b);
	free(boards);
}

char	**init_board(void)
{
	int		i;
	int		j;
	char	**board;

	i = 0;
	board = (char **)calloc(TOTAL_COLUMNS, sizeof(char *));
	if (!board)
		return (NULL);
	while (i < TOTAL_COLUMNS)
	{
		board[i] = (char *)calloc(TOTAL_COLUMNS, sizeof(char));
		if (!board[i])
		{
			j = 0;
			while (j < i)
			{
				free(board[j]);
				j++;
			}
			free(board);
			return (NULL);
		}
		i++;
	}
	return (board);
}

t_boards	*initialize(void)
{
	t_boards	*boards;

	boards = (t_boards *)calloc(1, sizeof(t_boards));
	if (!boards)
		return (NULL);
	boards->board_a = init_board();
	boards->board_b = init_board();
	if (!(boards->board_a && boards->board_b))
		return (NULL);
	boards->which = A;
	boards->grav_end_x = NULL;
	boards->grav_end_y = NULL;
	boards->grav_start_x = NULL;
	boards->grav_start_y = NULL;
	boards->grav_color = NULL;
	return (boards);
}
