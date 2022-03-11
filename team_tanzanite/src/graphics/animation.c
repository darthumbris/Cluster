#include "cluster.h"
#include "graphics.h"
#include "move.h"
#include <stdio.h>
#include <math.h>

void	alloc_board_tiles_falling(t_cluster *cluster, int tile_count)
{
	cluster->boards->grav_end_x = calloc(tile_count, sizeof(int));
	cluster->boards->grav_end_y = calloc(tile_count, sizeof(int));
	cluster->boards->grav_start_x = calloc(tile_count, sizeof(int));
	cluster->boards->grav_start_y = calloc(tile_count, sizeof(int));
	cluster->boards->grav_color = calloc(tile_count, sizeof(int));
	cluster->boards->fallen = calloc(tile_count, sizeof(int));
	if (!cluster->boards->grav_end_x || !cluster->boards->grav_end_y ||
		!cluster->boards->grav_start_x || !cluster->boards->grav_start_y ||
		!cluster->boards->grav_color || !cluster->boards->fallen)
	{
		free(cluster->boards->grav_color);
		free(cluster->boards->grav_end_x);
		free(cluster->boards->grav_end_y);
		free(cluster->boards->grav_start_x);
		free(cluster->boards->grav_start_y);
		free(cluster->boards->fallen);
		cluster->boards->grav_color = NULL;
		cluster->boards->grav_end_x = NULL;
		cluster->boards->grav_end_y = NULL;
		cluster->boards->grav_start_x = NULL;
		cluster->boards->grav_start_y = NULL;
		cluster->boards->fallen = NULL;
	}
}

int	get_amount_tiles_above(char **board, int i, int j)
{
	int	tiles_above;

	tiles_above = 0;
	if (i && j)
	{
		i--;
		j--;
	}
	else
		return (0);
	while (i && j)
	{
		if (!board[i][j])
			tiles_above++;
		i--;
		j--;
	}
	if (!board[i][j])
		tiles_above++;
	return (tiles_above);
}

void	set_board_grav_values(t_cluster *cluster)
{
	int		i;
	int		tile_count;
	int		j;
	int		k;
	float	width;
	int		tiles_above;

	k = 0;
	tile_count = count_tiles(cluster->boards->board_a);
	width = get_hex_width(HEX_HEIGHT);
	i = 0;
	while (i < TOTAL_COLUMNS && k < tile_count)
	{
		j = 0;
		while (j < TOTAL_COLUMNS)
		{
			if (cluster->boards->which == B)
			{
				if (cluster->boards->board_a[i][j])
				{
					tiles_above = get_amount_tiles_above(cluster->boards->board_a, i, j);
					cluster->boards->grav_end_x[k] = offset_width(j - tiles_above, i - tiles_above, width);
					cluster->boards->grav_end_y[k] = offset_height(i - tiles_above, j - tiles_above);
					cluster->boards->grav_color[k] = get_color(cluster->boards->board_a[i][j]);
					cluster->boards->grav_start_x[k] = offset_width(j, i, width);
					cluster->boards->grav_start_y[k] = offset_height(i, j);
					if (cluster->boards->grav_start_y[k] >= cluster->boards->grav_end_y[k])
						cluster->boards->fallen[k] = 1;
					k++;
				}
			}
			else
			{
				if (cluster->boards->board_b[i][j])
				{
					tiles_above = get_amount_tiles_above(cluster->boards->board_b, i, j);
					cluster->boards->grav_end_x[k] = offset_width(j - tiles_above, i - tiles_above, width);
					cluster->boards->grav_end_y[k] = offset_height(i - tiles_above, j - tiles_above);
					cluster->boards->grav_color[k] = get_color(cluster->boards->board_b[i][j]);
					cluster->boards->grav_start_x[k] = offset_width(j, i, width);
					cluster->boards->grav_start_y[k] = offset_height(i, j);
					if (cluster->boards->grav_start_y[k] >= cluster->boards->grav_end_y[k])
						cluster->boards->fallen[k] = 1;
					k++;
				}
			}
			j++;
		}
		i++;
	}
}

int	count_tiles(char **board)
{
	int	i;
	int	j;
	int	tile_count;

	i = 0;
	tile_count = 0;
	while (i < TOTAL_COLUMNS)
	{
		j = 0;
		while (j < TOTAL_COLUMNS)
		{
			if (board[i][j])
				tile_count++;
			j++;
		}
		i++;
	}
	return (tile_count);
}

int	get_end_i(int start_i, int start_j, t_boards *boards)
{
	while (start_i > 0 && start_j > 0)
	{
		if (boards->which == A)
		{
			if (boards->board_a[start_i][start_j])
				return (start_i);
		}
		else
		{
			if (boards->board_b[start_i][start_j])
				return (start_i);
		}
		start_i--;
		start_j--;
	}
	return (start_i);
}

int	get_end_j(int start_i, int start_j, t_boards *boards)
{
	while (start_i > 0 && start_j > 0)
	{
		if (boards->which == A)
		{
			if (boards->board_a[start_i][start_j])
				return (start_j);
		}
		else
		{
			if (boards->board_b[start_i][start_j])
				return (start_j);
		}
		start_i--;
		start_j--;
	}
	return (start_j);
}

void    draw_falling_tile(t_cluster *cluster)
{
    float   hex_height;
    hex_height = HEX_HEIGHT;
    if (cluster->boards->start_y < cluster->boards->end_y)
    {
        if (cluster->boards->which == A)
            draw_hexagon(cluster->boards->start_y, cluster->boards->start_x, \
                    cluster->boards->color, cluster->bgbuffer, hex_height);
        else
            draw_hexagon(cluster->boards->start_y, cluster->boards->start_x, \
                    cluster->boards->color, cluster->bgbuffer, hex_height);
    }
    else
    {
        if (cluster->boards->which == A)
            draw_hexagon(cluster->boards->end_y, cluster->boards->end_x, \
                    cluster->boards->color, cluster->bgbuffer, hex_height);
        else
            draw_hexagon(cluster->boards->end_y, cluster->boards->end_x, \
                    cluster->boards->color, cluster->bgbuffer, hex_height);
        cluster->col_anim = false;
    }
}

void	move_grav_positions(t_cluster *cluster)
{
	int	i;
	int	tile_count;

	tile_count = count_tiles(cluster->boards->board_a);
	if (!tile_count)
	{
		cluster->grav_anim = false;
		free_grav_tiles(cluster);
		return ;
	}
	i = 0;
	while (i < tile_count)
	{
		if (cluster->boards->fallen[i] == 0)
			cluster->boards->grav_start_y[i] += 20 * ANIM_SPEED_MODIFIER;
		i++;
	}
}

void	free_grav_tiles(t_cluster *cluster)
{
	if (cluster && cluster->boards && cluster->boards->grav_color)
	{
		free(cluster->boards->grav_color);
		free(cluster->boards->grav_end_x);
		free(cluster->boards->grav_end_y);
		free(cluster->boards->grav_start_x);
		free(cluster->boards->grav_start_y);
		free(cluster->boards->fallen);
		cluster->boards->grav_color = NULL;
		cluster->boards->grav_end_x = NULL;
		cluster->boards->grav_end_y = NULL;
		cluster->boards->grav_start_x = NULL;
		cluster->boards->grav_start_y = NULL;
		cluster->boards->fallen = NULL;
	}
}

void	draw_gravity(t_cluster *cluster)
{
	float   hex_height;
	int		tile_count;
	int		i;
	int		fallen;

	tile_count = count_tiles(cluster->boards->board_a);
	hex_height = HEX_HEIGHT;
	fallen = 0;
	if (!tile_count)
	{
		cluster->grav_anim = false;
		return ;
	}
	i = 0;
	while (i < tile_count)
	{
		if (cluster->boards->grav_start_y[i] < cluster->boards->grav_end_y[i])
			draw_hexagon(cluster->boards->grav_start_y[i], cluster->boards->grav_start_x[i],
				cluster->boards->grav_color[i], cluster->bgbuffer, hex_height);
		else
		{
			cluster->boards->fallen[i] = 1;
			draw_hexagon(cluster->boards->grav_end_y[i], cluster->boards->grav_end_x[i],
				cluster->boards->grav_color[i], cluster->bgbuffer, hex_height);
		}
		i++;
	}
	i = 0;
	while (i < tile_count)
	{
		if (cluster->boards->fallen[i])
			fallen++;
		i++;
	}
	if (fallen == tile_count)
	{
		cluster->grav_anim = false;
		free_grav_tiles(cluster);
	}
}

//	because otherwise its inside of the input
void	animation_setup(t_cluster *cluster)
{
	int			start_i;
	int			start_j;
	int			end_i;
	int			end_j;
	float		width;

	if (cluster->current_move.input == column)
	{
		start_i = translate(cluster->current_move.data.column_data.column).x;
		start_j = translate(cluster->current_move.data.column_data.column).y;
		width = get_hex_width(HEX_HEIGHT);
		cluster->boards->start_x = offset_width(start_j, start_i, width);
		cluster->boards->start_y = offset_height(start_i, start_j);
		end_i = get_end_i(start_i, start_j, cluster->boards);
		end_j = get_end_j(start_i, start_j, cluster->boards);
		cluster->boards->end_x = offset_width(end_j, end_i, width);
		cluster->boards->end_y = offset_height(end_i, end_j);
		if (cluster->boards->which == A)
			cluster->boards->color = get_color(cluster->boards->board_a[end_i][end_j]);
		else
			cluster->boards->color = get_color(cluster->boards->board_b[end_i][end_j]);
		if (start_i != end_i && start_j != end_j)
			cluster->col_anim = true;
	}
	else if (cluster->current_move.input == rotation)
	{
		alloc_board_tiles_falling(cluster, count_tiles(cluster->boards->board_a));
		set_board_grav_values(cluster);
		cluster->angle =  0;
		cluster->rot_anim = true;
		cluster->angle_end = cluster->current_move.data.rotation * ANGLE;
		if (cluster->current_move.data.rotation == 3)
			cluster->total_rotations = 7;
		if (cluster->current_move.data.rotation == 1)
			cluster->total_rotations = 5;
		if (cluster->current_move.data.rotation == 2)
			cluster->total_rotations = 6;
		if (cluster->current_move.data.rotation == 4)
			cluster->total_rotations = 7;
		if (cluster->current_move.data.rotation == 5)
			cluster->total_rotations = 5;
		cluster->current_rotation = 0;
	}
}

uint32_t _get_current_pixel_bg(int x, int y, t_cluster *cluster)
{
	uint32_t	current_pixel;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (y >= g_options.screen_height)
		y = g_options.screen_height - 1;
	if (x >= g_options.screen_width)
		x = g_options.screen_width - 1;

	current_pixel = BACKGROUND_COLOR;
	current_pixel |= ((cluster->bgbuffer->pixels[(y
		* cluster->bgbuffer->width + x) * sizeof(uint32_t)]) << 24 & 0xFF000000);
	current_pixel |= ((cluster->bgbuffer->pixels[(y
		* cluster->bgbuffer->width + x) * sizeof(uint32_t) + 1]) << 16 & 0xFF0000);
	current_pixel |= ((cluster->bgbuffer->pixels[(y
		* cluster->bgbuffer->width + x) * sizeof(uint32_t) + 2]) << 8 & 0xFF00);
	current_pixel |= ((cluster->bgbuffer->pixels[(y
		* cluster->bgbuffer->width + x) * sizeof(uint32_t) + 3]) & 0xFF);
	return (current_pixel);
}

void	_rotated_hex_draw(int i, int j, uint32_t color, mlx_image_t *img, float angle)
{
	float	x, y;
	int	rotate_x, rotate_y;


	x = offset_width(i, j, get_hex_width(HEX_HEIGHT));
	y = offset_height(i, j);
	//dprintf(STDOUT_FILENO, "1: %f, %f\n", x, y);
	x -= offset_width(g_options.board_width - 1, g_options.board_width - 1, get_hex_width(HEX_HEIGHT));//g_options.screen_width / 2;
	y -= offset_height(g_options.board_width - 1, g_options.board_width - 1); //g_options.screen_height / 2;
	//dprintf(STDOUT_FILENO, "2: %f, %f\n", x, y);
	rotate_x = x * cos(angle) + y * sin(angle);
	rotate_y = -x * sin(angle) + y * cos(angle);
	rotate_x += offset_width(g_options.board_width - 1, g_options.board_width - 1, get_hex_width(HEX_HEIGHT));//g_options.screen_width / 2;
	rotate_y += offset_height(g_options.board_width - 1, g_options.board_width - 1);//g_options.screen_height / 2;
	draw_hexagon(rotate_y, rotate_x, color, img, HEX_HEIGHT);
}

void	draw_rotation(t_cluster *cluster)
{
	static float	rotation_angle_curr;
	static float	rotation_angle_target;
	int				i;
	int				j;
	char			**board;

	board = cluster->animation_board;
	cluster_clear_screen(cluster->bgbuffer, BACKGROUND_COLOR);
	if (cluster->current_rotation == 0)
	{
		rotation_angle_curr = 0;
		rotation_angle_target = ((6 - cluster->current_move.data.rotation) / 6.0) * 2 * M_PI;
		cluster->current_rotation = 1;
	}
	if (rotation_angle_curr > rotation_angle_target)
	{
		cluster->rot_anim = false;
		cluster->grav_anim = true;
		cluster->current_rotation = 0;
	}
	i = 0;
	while (i < g_options.board_width)
	{
		j = 0;
		while (j < g_options.board_width + i)
		{
			if (board[j][i] != 0)
			{
				_rotated_hex_draw(i, j, get_color(board[j][i]), cluster->bgbuffer, rotation_angle_curr);
			}

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
				_rotated_hex_draw(i, j, get_color(board[j][i]), cluster->bgbuffer, rotation_angle_curr);
			}
			j++;
		}
		i++;
	}
	rotation_angle_curr += 0.04 * ANIM_SPEED_MODIFIER;
}

void	_draw_rotation(t_cluster *cluster)
{
	double			i;
	double			j;
	uint32_t	*rotate_buff;
	uint32_t	color;
	double			rotate_y;
	double			rotate_x;
	int				k;
	int				offset_x;
	int				offset_y;
	
	if (cluster->current_rotation < cluster->total_rotations)
	{
		//printf("angle: %f\n", cluster->angle);
		i = 0;
		k = 0;
		offset_y = g_options.screen_height / 2 + HEX_HEIGHT;
		offset_x = g_options.screen_width / 2;
		rotate_buff = calloc(((offset_y * 2) * (offset_x * 2)), sizeof(uint32_t));
		i = 1 - offset_y;
		while (i < offset_y)
		{
			j = 1 - offset_x;
			while (j < offset_x)
			{
				//printf("angle: %f\n", cluster->angle);
				rotate_x = j * cos(cluster->angle) - i * sin(cluster->angle);
				rotate_y = j * sin(cluster->angle) + i * cos(cluster->angle);
				if (rotate_y < 1 - offset_y)
					rotate_y = 1 - offset_y;
				if (rotate_y >= offset_y)
					rotate_y = offset_y - 1;
				if (rotate_x < 1 - offset_x)
					rotate_x = 1 - offset_x;
				if (rotate_x >= offset_x)
					rotate_x = offset_x - 1;
				color = _get_current_pixel_bg((int)(rotate_x + offset_x - 1), (int)(rotate_y + offset_y - 1), cluster);
				rotate_buff[k] = color;
				k++;
				j++;
			}
			i++;
		}
		//setting the rotate buff to the image
		i = 1 - offset_y;
		k = 0;
		//offset_height(BOARD_WIDTH, BOARD_WIDTH);
		while (i < offset_y && (i + offset_y - 1) < SCREEN_HEIGHT)
		{
			j = 1 - offset_x;
			while (j < offset_x && (j + offset_x - 1) < SCREEN_WIDTH)
			{
//				printf("offset_y: %d, offset_x: %d, i + offset_y - 1: %f, j + offset_x - 1: %f\n", offset_y, offset_x, i + offset_y - 1, j + offset_x - 1);
//				fflush(0);
				mlx_put_pixel(cluster->bgbuffer, j + offset_x - 1, i + offset_y - 1, rotate_buff[k]);
				k++;
				j++;
			}
			i++;
		}
		free(rotate_buff);
	}
	else
	{
		cluster->rot_anim = false;
		cluster->angle_end = 0;
		cluster->angle = 0;
		cluster->grav_anim = true;
		cluster->current_rotation = 0;
		cluster->total_rotations = 0;
	}
}
