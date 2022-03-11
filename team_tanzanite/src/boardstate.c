/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   boardstate.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 16:12:52 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/08 16:56:00 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

/*
**	NOT WORKING
*/

char	*boardstate_to_raw(char **board, int size)
{
	char	*raw;

	raw = malloc(sizeof(char) * (1 + size));
	if (raw == NULL)
		return (NULL);
	memcpy(raw, board, size);
	raw[size + 1] = '\0';
	return (raw);
}

char	**boardstate_from_raw(char *raw, int w, int h)
{
	int		y;
	char	**board;

	board = calloc(1, h * sizeof(char *));
	if (board == NULL)
		return (NULL);
	*board = calloc(1, w * h * sizeof(char));
	if (*board == NULL)
	{
		free(board);
		return (NULL);
	}
	memcpy(*board, raw, w * h * sizeof(char));
	y = 1;
	while (y < h + 1)
	{
		board[y] = &((*board)[w * y]);
		y++;
	}
	return (board);
}
