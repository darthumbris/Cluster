//#include "graphics.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cluster.h"
#include "graphics.h"

void	draw_bag(t_cluster *cluster, float hex_height)
{
	int			i;
	uint32_t	color;
	float		width;

	i = 0;
	width = get_hex_width(hex_height) / 4;
	while (i < g_options.color_amount_per_turn)
	{
		color = get_color(cluster->player[0].tokens_in_hand[i]);
		if (cluster->player[0].tokens_in_hand[i] && cluster->active_player == 0)
		{
			draw_hexagon(i * hex_height + (i + 1) * (hex_height / 5), \
				width, (color | 0x100), cluster->buffer, hex_height);
			draw_hexagon_outline(i * hex_height + (i + 1) * (hex_height / 5), \
				width, cluster->buffer, hex_height);
		}
		// If we can clear part of the screen before this function is called
		// (maybe in draw_ui?), this else block can be removed so we don't
		// show an "empty" token to the user.
		else
		{
			draw_hexagon(i * hex_height + (i + 1) * (hex_height / 5), \
			width, BACKGROUND_COLOR, cluster->buffer, hex_height);
			draw_hexagon_outline(i * hex_height + (i + 1) * (hex_height / 5), \
				width, cluster->buffer, hex_height);
		}
		
		color = get_color(cluster->player[1].tokens_in_hand[i]);
		if (cluster->player[1].tokens_in_hand[i] && cluster->active_player == 1)
		{
			draw_hexagon(i * hex_height + (i + 1) * (hex_height / 5), \
				g_options.screen_width - (5 * width), (color | 0x100), cluster->buffer, \
				hex_height);
			draw_hexagon_outline(i * hex_height + (i + 1) * (hex_height / 5), \
				g_options.screen_width - (5 * width), cluster->buffer, \
				hex_height);
		}
		// If we can clear part of the screen before this function is called
		// (maybe in draw_ui?), this else block can be removed so we don't
		// show an "empty" token to the user.
		else
		{
			draw_hexagon(i * hex_height + (i + 1) * (hex_height / 5), \
			g_options.screen_width - (5 * width), BACKGROUND_COLOR, cluster->buffer, \
			hex_height);
			draw_hexagon_outline(i * hex_height + (i + 1) * (hex_height / 5), \
				g_options.screen_width - (5 * width), cluster->buffer, \
				hex_height);
		}
		i++;
	}
}

static void	draw_arrows(t_cluster *cluster, float hex_height, float width, int to_highlight)
{
	int		i;
	int		offset_col;
	int		offset_h;
	float	h_x;
	float	h_y;

	i = - (g_options.board_width - 1);
	while (i < g_options.board_width)
	{
		offset_col = g_options.screen_width / 2 - width - i * width * 3;
		if (i <= 0)
			offset_h = (hex_height * (1 - i)) / 2;
		else if (i > 0)
			offset_h = (hex_height * (1 + i)) / 2;
		h_y = hex_height / 5;
		h_x = width;
		while (h_y < hex_height)
		{
			if (to_highlight && to_highlight - g_options.board_width == i)
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y++, get_color(cluster->drag_color));
			else
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y++, WHITE);

		}
		h_y = hex_height / 2;
		while (h_y < hex_height)
		{
			h_x = width - (((hex_height) - h_y) / tan(ANGLE));
			if (to_highlight && to_highlight - g_options.board_width == i)
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y, get_color(cluster->drag_color));
			else
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y, WHITE);
			h_x = width + (((hex_height) - h_y) / tan(ANGLE));
			if (to_highlight && to_highlight - g_options.board_width == i)
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y, get_color(cluster->drag_color));
			else
				mlx_put_pixel(cluster->buffer, offset_col + h_x, offset_h + h_y, WHITE);
			h_y++;
		}
		i++;
	}
}

void	draw_ui(t_cluster *cluster, int to_highlight)
{
	float	width;
	float	hex_height;

	if (!g_options.enable_ui)
		return ;
	hex_height = get_hex_height();
	width = get_hex_width(hex_height) / 4;
	if (g_options.color_amount_per_turn == 2)
	{
		mlx_draw_texture(cluster->buffer, cluster->lclick_icon, 106, 25);
		mlx_draw_texture(cluster->buffer, cluster->lclick_icon, g_options.screen_width - 164, 25);
		// If we can clear part of the screen, we can use the following if
		// statements to only draw the right mouse button if we have drawn two
		// tokens.
		// if (cluster->player[0].tokens_in_hand[1])
		mlx_draw_texture(cluster->buffer, cluster->rclick_icon, 110, 110);
		// if (cluster->player[1].tokens_in_hand[1])
		mlx_draw_texture(cluster->buffer, cluster->rclick_icon, g_options.screen_width - 160, 110);
	}
	draw_arrows(cluster, hex_height, width, to_highlight);
	draw_bag(cluster, 70);
	draw_hexagon(offset_height(TOTAL_COLUMNS, TOTAL_COLUMNS), offset_width(TOTAL_COLUMNS, TOTAL_COLUMNS, width * 4), get_color(-5),
				cluster->buffer, hex_height);
	draw_hexagon(offset_height((g_options.board_width - 1), TOTAL_COLUMNS), offset_width((g_options.board_width - 1), TOTAL_COLUMNS, width * 4), get_color(-6),
				cluster->buffer, hex_height);
	draw_hexagon(offset_height(TOTAL_COLUMNS, (g_options.board_width - 1)), offset_width(TOTAL_COLUMNS, (g_options.board_width - 1), width * 4), get_color(-7),
				cluster->buffer, hex_height);
	draw_hexagon(offset_height(-1, (g_options.board_width - 1)), offset_width(-1, (g_options.board_width - 1), width * 4), get_color(-8),
				cluster->buffer, hex_height);
	draw_hexagon(offset_height((g_options.board_width - 1), -1), offset_width((g_options.board_width - 1), -1, width * 4), get_color(-9),
				cluster->buffer, hex_height);
	// mlx_draw_texture(cluster->buffer, cluster->mclick_icon, offset_width(TOTAL_COLUMNS, TOTAL_COLUMNS, width * 4) + 30, offset_height(TOTAL_COLUMNS, TOTAL_COLUMNS) + 25);
	// mlx_draw_texture(cluster->buffer, cluster->mclick_icon, offset_width((g_options.board_width - 1), TOTAL_COLUMNS, width * 4) + 30, offset_height((g_options.board_width - 1), TOTAL_COLUMNS) + 25);
	// mlx_draw_texture(cluster->buffer, cluster->mclick_icon, offset_width(TOTAL_COLUMNS, (g_options.board_width - 1), width * 4) + 30, offset_height(TOTAL_COLUMNS, (g_options.board_width - 1)) + 25);
	// mlx_draw_texture(cluster->buffer, cluster->mclick_icon, offset_width(-1, (g_options.board_width - 1), width * 4) + 30, offset_height(-1, (g_options.board_width - 1)) + 25);
	// mlx_draw_texture(cluster->buffer, cluster->mclick_icon, offset_width((g_options.board_width - 1), -1, width * 4) + 25, offset_height((g_options.board_width - 1), -1) + 25);
}
