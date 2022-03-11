/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 17:31:13 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/11 10:49:08 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "move.h"

static const char	*_get_cmd(t_input cmd)
{
	static const char	*commands[] =
	{
		[column] = "column",
		[rotation] = "rotate",
		[invalid] = "invalid"
	};
	return (commands[cmd]);
}

void	_to_stdout(t_cluster *cluster)
{
	//	player
	dprintf(STDOUT_FILENO, "Player %d: ", cluster->active_player + 1);
	//	command
	dprintf(STDOUT_FILENO, "%s ", _get_cmd(cluster->current_move.input));
	//	then number of column/rotation
	if (cluster->current_move.input == column)
		dprintf(STDOUT_FILENO, "%d ", cluster->current_move.data.column_data.column);
	else if (cluster->current_move.input == rotation)
		dprintf(STDOUT_FILENO, "%d ", cluster->current_move.data.rotation);
	//	then color if column
	if (cluster->current_move.input == column)
		dprintf(STDOUT_FILENO, "%d ", cluster->current_move.data.column_data.colour);
	dprintf(STDOUT_FILENO, "\n");
}

void	output_announce_winner(t_cluster *cluster, t_player *winner)
{
	int	loser;

	loser = 0;
	if (winner->index == 0)
		loser = 1;
	dprintf(STDOUT_FILENO, "Player %d won!\n", winner->index + 1);
	dprintf(STDOUT_FILENO, "Player %d lost...\n", loser + 1);
	if (BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
		{
			dprintf(cluster->player[0].io[1], "Player %d %s won!\n",
				winner->index + 1, ((winner->index == 0) ? "(you)" : ""));
			dprintf(cluster->player[0].io[1], "Player %d %s lost...\n",
				loser + 1, ((loser == 0) ? "(you)" : ""));
		}
		if (cluster->player[1].how_verbose > 0)
		{
			dprintf(cluster->player[1].io[1], "Player %d %s won!\n",
				winner->index + 1, ((winner->index == 1) ? "(you)" : ""));
			dprintf(cluster->player[1].io[1], "Player %d %s lost...\n",
				loser + 1, ((loser == 1) ? "(you)" : ""));
		}
	}
	if (winner->index == 0)
		cluster->win_msg = mlx_put_string(cluster->mlx, "Player 1 WINS!", g_options.screen_width/4, 10);
	else
		cluster->win_msg = mlx_put_string(cluster->mlx, "Player 2 WINS!", g_options.screen_width/2 + 60, 10);
	//mlx_resize_image(cluster->win_msg, cluster->win_msg->height, cluster->win_msg->width);
}

	// Output: <COMMAND> <X (for COLUMN/ROTATION)> [COLOR] <RAW BOARDSTATE>
	//	TODO: move to seperate function(s) outside of loop file
static void	_to_bots(t_cluster *cluster)
{
	int	i;

	if (cluster->current_move.input == column && BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
			dprintf(cluster->player[0].io[1], "column %d %d",
				cluster->current_move.data.column_data.column,
				cluster->current_move.data.column_data.colour);
		if (cluster->player[1].how_verbose > 0)
			dprintf(cluster->player[1].io[1], "column %d %d",
				cluster->current_move.data.column_data.column,
				cluster->current_move.data.column_data.colour);
	}
	else if (cluster->current_move.input == rotation && BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
			dprintf(cluster->player[0].io[1],"rotation %d", cluster->current_move.data.rotation);
		if (cluster->player[1].how_verbose > 0)
			dprintf(cluster->player[1].io[1],"rotation %d", cluster->current_move.data.rotation);
	}
	else if (cluster->current_move.input != verbosity && BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
			dprintf(cluster->player[0].io[1], "invalid");
		if (cluster->player[1].how_verbose > 0)
			dprintf(cluster->player[1].io[1], "invalid");
	}
	if (BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
		{
			dprintf(cluster->player[0].io[1], " next: player%d %s colors: ",
				cluster->active_player + 1,
				((cluster->active_player == 0) ? "(you)" : ""));
			i = 0;
			while (i <= g_options.colors_to_play)
			{
				if (cluster->player[cluster->active_player].tokens_in_hand[i])
					dprintf(cluster->player[0].io[1], "%d ", cluster->player[cluster->active_player].tokens_in_hand[i]);
				i++;
			}
			dprintf(cluster->player[0].io[1], "\n");
		}
		if (cluster->player[1].how_verbose > 0)
		{
			dprintf(cluster->player[1].io[1], " next: player%d %s colors: ",
				cluster->active_player + 1,
				((cluster->active_player == 1) ? "(you)" : ""));
			i = 0;
			while (i <= g_options.colors_to_play)
			{
				if (cluster->player[cluster->active_player].tokens_in_hand[i])
					dprintf(cluster->player[1].io[1], "%d ", cluster->player[cluster->active_player].tokens_in_hand[i]);
				i++;
			}
			dprintf(cluster->player[1].io[1], "\n");
		}
		visualize_text(cluster);
	}
}

void	output(t_cluster *cluster)
{
	_to_stdout(cluster);
	_to_bots(cluster);
}
