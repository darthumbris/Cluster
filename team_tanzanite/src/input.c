/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 13:33:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include <stdio.h>

static int	ft_fabs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	mouse_x_to_column(int x)
{
	int		i;
	float	width;
	float	offset_col;

	width = get_hex_width(get_hex_height()) / 4;
	i = - (g_options.board_width - 1);;
	while (i < g_options.board_width)
	{
		offset_col = g_options.screen_width / 2 - width - i * width * 3 + width;
		if (ft_fabs(offset_col - x) <  width)
			return (i + g_options.board_width);
		i++;
	}
	return (0);
}

static bool	_are_we_there_yet(t_cluster *cluster)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (now.tv_sec > cluster->next_play.tv_sec
		|| (now.tv_sec == cluster->next_play.tv_sec &&
		now.tv_usec > cluster->next_play.tv_usec))
		return (true);
	return (false);
}

//	? Needs to be moved to graphics ?
static	int	update_ui(t_cluster *cluster)
{
	int	x;
	int	y;
	int	out;

	mlx_get_mouse_pos(cluster->mlx, &x, &y);
	out = mouse_x_to_column(x);
	draw_ui(cluster, out);
	return (out);
}

static void	_set_next_play(t_cluster *cluster)
{
	gettimeofday(&(cluster->next_play), NULL);
	cluster->next_play.tv_usec += g_options.delay_us;
	while (cluster->next_play.tv_usec >= 1000000)
	{
		(cluster->next_play.tv_usec) -= 1000000;
		(cluster->next_play.tv_sec)++;
	}
}

uint32_t _get_current_pixel(t_cluster *cluster)
{
	int			x;
	int			y;
	uint32_t	current_pixel;

	current_pixel = 0;
	mlx_get_mouse_pos(cluster->mlx, &x, &y);
	//	Likely want a get_pixel function
	current_pixel |= ((cluster->buffer->pixels[(y
		* cluster->buffer->width + x) * sizeof(uint32_t)]) << 24 & 0xFF000000);
	current_pixel |= ((cluster->buffer->pixels[(y
		* cluster->buffer->width + x) * sizeof(uint32_t) + 1]) << 16 & 0xFF0000);
	current_pixel |= ((cluster->buffer->pixels[(y
		* cluster->buffer->width + x) * sizeof(uint32_t) + 2]) << 8 & 0xFF00);
	current_pixel |= ((cluster->buffer->pixels[(y
		* cluster->buffer->width + x) * sizeof(uint32_t) + 3]) & 0xFF);
	return (current_pixel);
}

//	Bit of a mess
void	mouse_input_stuff(t_cluster *cluster)
{
	uint32_t	current_pixel;
	char		*out;
	int			i;
	int			col;

	if (!_are_we_there_yet(cluster))
		return ;
	out = NULL;
	col = update_ui(cluster);
	if (mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_MIDDLE))
	{
		current_pixel = _get_current_pixel(cluster);
		//	!!Magic numbers!!
		if ((current_pixel) == get_color(-5))
			out = "rotate 3";
		else if ((current_pixel) == get_color(-6))
			out = "rotate 4";
		else if ((current_pixel) == get_color(-7))
			out = "rotate 2";
		else if ((current_pixel) == get_color(-8))
			out = "rotate 5";
		else if ((current_pixel) == get_color(-9))
			out = "rotate 1";
		if (out != NULL)
		{
			dprintf(cluster->player[cluster->active_player].io[2], "%s\n", out);
			_set_next_play(cluster);
		}
	}

	// In the case of only one piece per turn or in hand, only use the left mouse button.
	if ((!cluster->player[cluster->active_player].tokens_in_hand[1])
			|| g_options.color_amount_per_turn == 1)
	{
		if (col)
		{
			// Upper piece
			if (mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_LEFT))
			{
				dprintf(cluster->player[cluster->active_player].io[2],
					"column %d %d\n", (g_options.board_width - col),
					cluster->player[cluster->active_player].tokens_in_hand[0]);
				_set_next_play(cluster);
			}
		}
	}
	// If two pieces per turn are drawn, work with left and right mouse button.
	else if (g_options.color_amount_per_turn == 2)
	{
		if (col)
		{
			// Upper piece
			if (mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_LEFT))
			{
				dprintf(cluster->player[cluster->active_player].io[2],
					"column %d %d\n", (g_options.board_width - col),
					cluster->player[cluster->active_player].tokens_in_hand[0]);
				_set_next_play(cluster);
			}
			// Lower piece
			else if (mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_RIGHT))
			{
				dprintf(cluster->player[cluster->active_player].io[2],
					"column %d %d\n", (g_options.board_width - col),
					cluster->player[cluster->active_player].tokens_in_hand[1]);
				_set_next_play(cluster);
			}
		}
	}
	// If more than two  pieces per turn are drawn, let the user drag them to a column
	else
	{
		// Mouse clicked
		if (mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_LEFT) && !cluster->mouse_held_down)
		{
			cluster->mouse_held_down = true;
			// Blue channel has value 1. This happens only in our bag overview.
			if ((_get_current_pixel(cluster) & 0xFF00) == (1 << 8))
			{
				i = 1;
				// Loop through all colours
				while (i <= (g_options.players * g_options.colors_to_play))
				{
					// If colour i matches the clicked pixel if we ignore the blue channel, we have a match
					if (get_color(i) == (_get_current_pixel(cluster) & 0xFFFF00FF))
					{
						cluster->drag_color = i;
						break ;
					}
					i++;
				}
			}
		}
		// Mouse released
		if (!mlx_is_mouse_down(cluster->mlx, MLX_MOUSE_BUTTON_LEFT) && cluster->mouse_held_down)
		{
			cluster->mouse_held_down = false;
			if (col && cluster->drag_color)
			{
				i = 0;
				while (i < g_options.color_amount_per_turn)
				{
					if (cluster->player[cluster->active_player].tokens_in_hand[i]
						== cluster->drag_color)
					{
						dprintf(cluster->player[cluster->active_player].io[2],
							"column %d %d\n", (g_options.board_width - col),
							cluster->player[cluster->active_player].tokens_in_hand[i]);
						_set_next_play(cluster);
						break ;
					}
					i++;
				}
			}
			cluster->drag_color = 0;
		}
	}
}
