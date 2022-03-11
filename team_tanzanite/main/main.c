/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:28:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/10 20:50:37 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "move.h"
#include "fcntl.h"
#include "graphics.h"

static void	_init_players(t_player *players)
{
	players[0].index = 0;
	players[1].index = 1;
	player_set_playcolors(&(players[0]));
	player_set_playcolors(&(players[1]));
	player_fill_bag(&(players[0]));
	player_fill_bag(&(players[1]));
}

int	main(int argc, char **argv)
{
	t_cluster	*cluster;

	if (argc == 2)
		gobal_settings(argv[1]);
	//	Apparently this is important otherwise when reading input the program gets stuck
	int flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);
	//	Init program
	cluster = cluster_init(g_options.screen_width, g_options.screen_height, SCREEN_TITLE);
	if (cluster == NULL)
		return (EXIT_FAILURE);
	cluster_hooks(cluster);
	//	Board init
	cluster->boards = initialize();
	cluster->animation_board = init_board();
	if (cluster->boards == NULL)
	{
		cluster_clean(cluster);
		return (EXIT_FAILURE);
	}
	//	Player init
	_init_players(cluster->player);
	//	Initial draw calls
	draw_grid(cluster->buffer);
	draw_board(cluster->boards->board_a, cluster->bgbuffer, false);
	//	Start loop
	mlx_loop(cluster->mlx);
	//	Cleanup
	cluster_clean(cluster);
	return (EXIT_SUCCESS);
}
