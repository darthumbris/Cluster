/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:23:05 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 16:41:22 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"

void	move(t_boards *boards, t_parse *move)
{
	int failure;

	if (move->input == rotation)
		rotate_move(boards, move->data.rotation);
	else if (move->input == column)
	{
		failure = column_move(boards, move->data.column_data.column,
			move->data.column_data.colour);
		if (failure)
		{
			move->input = invalid;
			return ;
		}
	}
	gravity(boards);
}
