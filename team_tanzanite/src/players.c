/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   players.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 17:18:27 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:01 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include <stdio.h>

bool	player_is_bag_empty(t_player *player)
{
	if (player->amount_left == 0)
		return (true);
	return (false);
}

void	player_add_token(t_player *player, int token)
{
	if (token == 0)
		return ;
	if (player->amount_left >= TOTAL_TOKENS)
		return ;
	player->token_bag[player->amount_left] = token;
	player->amount_left += 1;
}

int		player_take_token(t_player *player)
{
	int	token;

	if (player->amount_left > 0)
	{
		player->amount_left -= 1;
		token = player->token_bag[player->amount_left];
		player->token_bag[player->amount_left] = 0;
		return (token);
	}
	return (0);
}

void	player_bag_shuffle(t_player *player)
{
	shuffle_array((char *)player->token_bag, player->amount_left);
}

bool	player_has_playcolor(t_player *player, int c)
{
	int	i;

	i = 0;
	while (i < g_options.colors_to_play)
	{
		if (player->token_colors[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	player_set_playcolors(t_player *player)
{
	int	i;

	i = 0;
	while (i < g_options.colors_to_play)
	{
		player->token_colors[i] = (unsigned char)(1 + (i * 2) + (player->index == 1));
		i++;
	}
}

void	player_print_bag(t_player *player)
{
	int	i;

	fprintf(stdout, "Player %d colorbag contains: [ ", player->index + 1);
	i = 0;
	while (i < player->amount_left)
	{
		fprintf(stdout, "%d ", (int)player->token_bag[i]);
		i++;
	}
	fprintf(stdout, "]\n");
}

void	player_fill_bag(t_player *player)
{
	int				i;
	int				j;
	int				token;

	i = 0;
	while (i < g_options.colors_to_play)
	{
		token = player->token_colors[i];
		j = 0;
		while (j < g_options.color_sets_in_bag)
		{
			player_add_token(player, token);
			j++;
		}
		i++;
	}
	player_bag_shuffle(player);
}

void	player_tokens_to_hand(t_player *player)
{
	int	i;

	player_bag_shuffle(player);
	i = 0;
	while (i < g_options.color_amount_per_turn)
	{
		player->tokens_in_hand[i] = player_take_token(player);
		i++;
	}
}
