/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualize_text.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 18:08:18 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "move.h"
#include <stdio.h>

void	real_visualize_text(char **board, t_player *players)
{
	t_coord	coord;

	coord.y = 0;
	while (coord.y < TOTAL_COLUMNS)
	{
		coord.x = 0;
		while (coord.x < TOTAL_COLUMNS)
		{
			if (players[0].how_verbose > 3)
			{
				if ((coord.x >= g_options.board_width && (coord.x - g_options.board_width) >= coord.y)
					|| (coord.y >= g_options.board_width && (coord.y - g_options.board_width) >= coord.x))
					dprintf(players[0].io[1], "x\t");
				else
					dprintf(players[0].io[1], "%d\t", (int)board[coord.x][coord.y]);
			}
			if (players[1].how_verbose > 3)
			{
				if ((coord.x >= g_options.board_width && (coord.x - g_options.board_width) >= coord.y)
					|| (coord.y >= g_options.board_width && (coord.y - g_options.board_width) >= coord.x))
					dprintf(players[1].io[1], "x\t");
				else
					dprintf(players[1].io[1], "%d\t", (int)board[coord.x][coord.y]);
			}
			(coord.x)++;
		}
		if (players[0].how_verbose > 3)
			dprintf(players[0].io[1], "\r");
		if (players[1].how_verbose > 3)
			dprintf(players[1].io[1], "\r");
		(coord.y)++;
	}
	if (players[0].how_verbose > 3)
		dprintf(players[0].io[1], "\n");
	if (players[1].how_verbose > 3)
		dprintf(players[1].io[1], "\n");
}

void	visualize_text(t_cluster *cluster)
{
	if (cluster->boards->which == A)
	{
		real_visualize_text(cluster->boards->board_a, cluster->player);
	}
	else
	{
		real_visualize_text(cluster->boards->board_b, cluster->player);
	}
}
