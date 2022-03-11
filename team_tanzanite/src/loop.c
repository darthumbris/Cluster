/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   loop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:41:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/11 10:49:07 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "move.h"
#include "graphics.h"
#include <stdio.h>

static t_gamestate	loop_state_init(t_cluster *cluster)
{
	t_player	*player;
	int			i;

	cluster->active_player = 0;
	player = &(cluster->player[cluster->active_player]);
	//print first player
	player_tokens_to_hand(player);
	player_tokens_to_hand(&(cluster->player[1]));
	draw_ui(cluster, 0);
	//	Initial print (?)
	if (BOTS)
	{
		if (cluster->player[0].how_verbose > 0)
		{
			dprintf(cluster->player[0].io[1], "next: player%d (you) colors: ",
				cluster->active_player + 1);
			i = 0;
			while (i < g_options.color_amount_per_turn)
			{
				if (player->tokens_in_hand[i])
					dprintf(cluster->player[0].io[1], "%d ", player->tokens_in_hand[i]);
				i++;
			}
			dprintf(cluster->player[0].io[1], "\n");
		}
		if (cluster->player[1].how_verbose > 0)
		{
			dprintf(cluster->player[1].io[1], "next: player%d colors: ",
				cluster->active_player + 1);
			i = 0;
			while (i < g_options.color_amount_per_turn)
			{
				if (player->tokens_in_hand[i])
					dprintf(cluster->player[1].io[1], "%d ", player->tokens_in_hand[i]);
				i++;
			}
			dprintf(cluster->player[1].io[1], "\n");
		}
	}
	return (STATE_HANDLE_INPUT);
}

static void	_put_back_tokens(t_parse *move, t_player *player)
{
	int	i;
	int	token;

	if (move->input != column)
		return ;
	i = 0;
	token = move->data.column_data.colour;
	while (i < g_options.color_amount_per_turn)
	{
		if (player->tokens_in_hand[i] == token)
			break ;
		player_add_token(player, player->tokens_in_hand[i]);
		i++;
	}
	i++;
	while (i < g_options.color_amount_per_turn)
	{
		player_add_token(player, player->tokens_in_hand[i]);
		i++;
	}
}

static void	_swap_active_player(t_cluster *cluster)
{
	if (cluster->active_player == 0)
		cluster->active_player = 1;
	else
		cluster->active_player = 0;
}

static t_player	*_get_active_player(t_cluster *cluster)
{
	return (&(cluster->player[cluster->active_player]));
}

static void	make_copy_of_board(t_cluster *cluster)
{
	char	**board;

	board = cluster->boards->board_b;
	if(cluster->boards->which == A)
		board = cluster->boards->board_a;
	copy_board(board, cluster->animation_board);
}

static t_gamestate	loop_state_input(t_cluster *cluster)
{
	t_player	*player;

	mouse_input_stuff(cluster);
	player = _get_active_player(cluster);
	if (get_input(&(cluster->current_move), player->io[0]))
	{
		if (BOTS && cluster->current_move.input == verbosity)
		{
			player->how_verbose = cluster->current_move.data.how_verbose;
			return (STATE_HANDLE_INPUT);
		}
		if (is_valid_move(&(cluster->current_move), player))
		{
			make_copy_of_board(cluster);
			move(cluster->boards, &(cluster->current_move));
			animation_setup(cluster); //	Should probably be converted to a animation struct
			_put_back_tokens(&(cluster->current_move), player);
		}
		_swap_active_player(cluster);
		player_tokens_to_hand(_get_active_player(cluster));
		_swap_active_player(cluster);
		if (cluster->col_anim || cluster->grav_anim || cluster->rot_anim)
			return (STATE_ANIMATION);
		return (STATE_DRAWING);
	}
	return (STATE_HANDLE_INPUT);
}

static t_gamestate	loop_state_draw(t_cluster *cluster)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cluster->mlx, &x, &y);
	cluster_clear_screen(cluster->bgbuffer, BACKGROUND_COLOR);
	if (cluster->boards->which == A)
		draw_board(cluster->boards->board_a, cluster->bgbuffer, false);
	else
		draw_board(cluster->boards->board_b, cluster->bgbuffer, false);
	//draw_grid(cluster->buffer);
	draw_ui(cluster, mouse_x_to_column(x));
	return (STATE_OUTPUT);
}

static t_gamestate	loop_state_animation(t_cluster *cluster)
{
	if(!g_options.enable_animation)
		return (STATE_DRAWING);
	if (cluster->col_anim)
	{
		cluster_clear_screen(cluster->bgbuffer, BACKGROUND_COLOR);
		//draw_grid(cluster->bgbuffer);
		if (cluster->boards->which == A)
			draw_board(cluster->boards->board_a, cluster->bgbuffer, false);
		else
			draw_board(cluster->boards->board_b, cluster->bgbuffer, false);
		//	Needs to be in a seperate function likely outside of this file
		draw_hexagon(cluster->boards->end_y, cluster->boards->end_x, BACKGROUND_COLOR, cluster->bgbuffer, HEX_HEIGHT);
		draw_falling_tile(cluster);
		//draw_hexagon_outline(cluster->boards->end_y, cluster->boards->end_x, cluster->bgbuffer, HEX_HEIGHT);
		//clean_edges(cluster);
		cluster->boards->start_y += 20 * ANIM_SPEED_MODIFIER;
		return (STATE_ANIMATION);
	}
	else if (cluster->grav_anim)
	{
		cluster_clear_screen(cluster->bgbuffer, BACKGROUND_COLOR);
		//draw_grid(cluster->buffer);
		//clean_edges(cluster);
		draw_gravity(cluster);
		if (cluster->grav_anim)
			move_grav_positions(cluster);
		return (STATE_ANIMATION);
	}
	else if (cluster->rot_anim)
	{
		draw_rotation(cluster);
		if (cluster->current_move.data.rotation >= 1 && cluster->current_move.data.rotation <= 3)
			cluster->angle -= 0.16;
		else
			cluster->angle += 0.16;
		cluster->current_rotation++;
		//cluster->angle += ANGLE;
		return (STATE_ANIMATION);
	}
		return (STATE_DRAWING);
}

static bool	_check_game_end(t_cluster *cluster)
{
	int			winner;
	t_player	*player;

	winner = winner_test(cluster->boards);
	player = _get_active_player(cluster);
	if (winner > 0)
	{
		if (player_has_playcolor(&(cluster->player[0]), winner))
			output_announce_winner(cluster, &(cluster->player[0]));
		else
			output_announce_winner(cluster, &(cluster->player[1]));
		return (true);
	}
	else if (player_is_bag_empty(player))
	{
		if (player->index == 0)
			output_announce_winner(cluster, &(cluster->player[1]));
		else
			output_announce_winner(cluster, &(cluster->player[0]));
		return (true);
	}
	return (false);
}

static t_gamestate	loop_state_output(t_cluster *cluster)
{
//	t_player	*player;

//	player = _get_active_player(cluster);
	if (_check_game_end(cluster))
		return (STATE_END);
	_swap_active_player(cluster);
	output(cluster);
	draw_ui(cluster, 0);
	return (STATE_HANDLE_INPUT);
}

void	loop_run(t_cluster *cluster)
{
	//	Close on ESC
	if (mlx_is_key_down(cluster->mlx, MLX_KEY_ESCAPE))
		cluster_close(cluster);
	//	Statemachine
	switch (cluster->state)
	{
		case STATE_INITIALIZATION :
			cluster->state = loop_state_init(cluster);
			break ;
		case STATE_HANDLE_INPUT :
			cluster->state = loop_state_input(cluster);
			break ;
		case STATE_ANIMATION :
			cluster->state = loop_state_animation(cluster);
			break ;
		case STATE_DRAWING :
			cluster->state = loop_state_draw(cluster);
			break ;
		case STATE_OUTPUT :
			cluster->state = loop_state_output(cluster);
			break ;
		case STATE_END :
			cluster->state = STATE_END;
//			cluster_close(cluster);
			break ;
		default :
			break ;
	}
}
