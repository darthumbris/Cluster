/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 13:38:00 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/10 20:51:20 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include <stdbool.h>
#include "parsing.h"

static bool	_invalid(t_parse *move)
{
	move->input = invalid;
	return (false);
}

static bool	_has_color(int color, t_player *player)
{
	int	i;

	i = 0;
	while (i < g_options.color_amount_per_turn)
	{
		if (player->tokens_in_hand[i] == color)
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_move(t_parse *move, t_player *player)
{
	if (move->input != column && move->input != rotation)
		return (_invalid(move));
	if (move->input == column)
	{
		if (move->data.column_data.colour == 0)
			_invalid(move);
		if (!_has_color(move->data.column_data.colour, player))
			_invalid(move);
	}
	if (move->input == rotation)
	{
		if (_has_color(0, player))
		{
			player->amount_left = 0;
			return (_invalid(move));
		}
	}
	return (true);
}
