/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_board.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:39:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/11 10:22:38 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cluster.h"
#include "graphics.h"

uint32_t	get_color(int i)
{
	uint8_t		channel;
	uint32_t	color;

	color = 0x000000ff;
	channel = 0xff;
	channel /= g_options.colors_to_play;
	channel *= (((i - (i % g_options.players)) / 2) + 1);
	if (i > 0)
	{
		if ((i % g_options.players) == 0)
			color |= channel << 24;
		else if ((i % g_options.players) == 1)
			color |= channel << 16;
		else if ((i % g_options.players) == 2)
		{
			color |= channel << 24;
			color |= channel << 16;
		}
		// Default to P1's colour until we find a fix.
		else
			color |= channel << 24;
		return (color);
	}
	else
	{
		const uint32_t	color[] = {
			0xd1da33ff,
			0xff00ffff,
			0x1b9527ff,
			0x781727ff,
			0x78a4edff,
			0x00ffffff,
			0x00fffffe,
			0x00ffffef,
			0x00fffeff,
			0x00ffefff
		};

		if (i <= 0 && i >= -9)
			return (color[-i]);
		else
			return (color[0]);
	}
}

float	get_hex_width(int height)
{
	return ((float)(4 * (height / 2 / sqrt(3))));
}

float	get_hex_height(void)
{
	return (g_options.screen_height / (2 * g_options.board_width + 2));
}

void	draw_hexagon(int row, int col, uint32_t color, mlx_image_t *img, float hex_height)
{
	float			h_x;
	float			h_y;
	float			width;

	width = get_hex_width(hex_height) / 4;
	h_y = 0;
	while (h_y < hex_height / 2)
	{
		h_x = width - (h_y / TAN_ANGLE);
		while (h_x < width * 3 + (h_y / TAN_ANGLE))
		{
			mlx_put_pixel(img, col + h_x, row + h_y, color);
			h_x++;
		}
		h_y++;
	}
	while (h_y < hex_height)
	{
		h_x = width - (((hex_height) - h_y) / tan(ANGLE));
		while (h_x < width * 3 + (((hex_height) - h_y) / tan(ANGLE)))
		{
			mlx_put_pixel(img, col + h_x, row + h_y, color);
			h_x++;
		}
		h_y++;
	}
	//draw_hexagon_outline(row, col, img, hex_height);
}

void	draw_hexagon_outline(int row, int col, mlx_image_t *img, float hex_height)
{
	float			h_x;
	float			h_y;
	float			width;

	width = get_hex_width(hex_height) / 4;
	h_y = 0;
	h_x = width;
	while (h_x < width * 3)
		mlx_put_pixel(img, col + h_x++, row + h_y, HEX_OUTLINE_COLOR);
	while (h_y < hex_height / 2)
	{
		h_x = width - (h_y / TAN_ANGLE);
		mlx_put_pixel(img, col + h_x, row + h_y, HEX_OUTLINE_COLOR);
		h_x = width * 3 + (h_y / TAN_ANGLE);
		mlx_put_pixel(img, col + h_x, row + h_y, HEX_OUTLINE_COLOR);
		h_y++;
	}
	while (h_y < hex_height)
	{
		h_x = width - (((hex_height) - h_y) / tan(ANGLE));
		mlx_put_pixel(img, col + h_x, row + h_y, HEX_OUTLINE_COLOR);
		h_x = width * 3 + (((hex_height) - h_y) / tan(ANGLE));
		mlx_put_pixel(img, col + h_x, row + h_y, HEX_OUTLINE_COLOR);
		h_y++;
	}
	h_x = width;
	while (h_x < width * 3)
		mlx_put_pixel(img, col + h_x++, row + h_y, HEX_OUTLINE_COLOR);
}

int	offset_height(int i, int j)
{
	return (g_options.screen_height - (1.5 * HEX_HEIGHT) - (HEX_HEIGHT / 2) * j - (HEX_HEIGHT / 2) * i);
}

int	offset_width(int i, int j, float width)
{
	return (g_options.screen_width / 2 - (j * 3 * width / 4) + (i * 3 * width / 4) - width / 2);
}

void	draw_grid(mlx_image_t *img)
{
	int		i;
	int		j;
	float	width;
	float	hex_height;

	if (!g_options.enable_grid)
		return ;
	i = 0;
	hex_height = HEX_HEIGHT;
	width = get_hex_width(hex_height);
	while (i < g_options.board_width)
	{
		j = 0;
		while (j < g_options.board_width + i)
		{
			//	draw_hexagon(offset_height(i, j), offset_width(i, j, width), get_color(0), img, hex_height);
			draw_hexagon_outline(offset_height(i, j), \
			offset_width(i, j, width), img, hex_height);
			j++;
		}
		i++;
	}
	while (i < 2 * g_options.board_width - 1)
	{
		j = i - g_options.board_width + 1;
		while (j < 2 * g_options.board_width - 1)
		{
			//	draw_hexagon(offset_height(i, j), offset_width(i, j, width), get_color(0), img, hex_height);
			draw_hexagon_outline(offset_height(i, j), \
			offset_width(i, j, width), img, hex_height);
			j++;
		}
		i++;
	}
}

void	draw_board(char **board, mlx_image_t *img, bool empty)
{
	int		i;
	int		j;
	float	width;
	float	hex_height;

	if (empty)
		return ;
	i = 0;
	hex_height = HEX_HEIGHT;
	width = get_hex_width(hex_height);
	while (i < g_options.board_width)
	{
		j = 0;
		while (j < g_options.board_width + i)
		{
			if (board[j][i] != 0)
			{
				if (empty)
					draw_hexagon(offset_height(i, j), offset_width(i, j, width), \
						BACKGROUND_COLOR, img, hex_height);
				else
					draw_hexagon(offset_height(i, j), offset_width(i, j, width), \
						get_color(board[j][i]), img, hex_height);
			}
			//draw_hexagon_outline(offset_height(i, j), offset_width(i, j, width), img, hex_height);
			j++;
		}
		i++;
	}
	while (i < 2 * g_options.board_width - 1)
	{
		j = i - g_options.board_width + 1;
		while (j < 2 * g_options.board_width - 1)
		{
			if (board[j][i] != 0)
			{
				if (empty)
					draw_hexagon(offset_height(i, j), offset_width(i, j, width), \
						BACKGROUND_COLOR, img, hex_height);
				else
					draw_hexagon(offset_height(i, j), offset_width(i, j, width), \
						get_color(board[j][i]), img, hex_height);
			}
			//draw_hexagon_outline(offset_height(i, j), offset_width(i, j, width), img, hex_height);
			j++;
		}
		i++;
	}
}

