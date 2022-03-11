/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:39:46 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/10 18:12:02 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

//	# include "cluster.h"

void		draw_board(char **board, mlx_image_t *img, bool empty);
void		draw_hexagon(int row, int col, uint32_t color, mlx_image_t *img, float hex_height);
float		get_hex_width(int height);
void		draw_grid(mlx_image_t *img);
void		draw_hexagon_outline(int row, int col, mlx_image_t *img, float hex_height);
void		draw_ui(t_cluster *cluster, int to_highlight);
float		get_hex_height(void);
uint32_t	get_color(int i);
int			offset_height(int i, int j);
int			offset_width(int i, int j, float width);
void		draw_falling_tile(t_cluster *cluster);
void		mouse_input_stuff(t_cluster *cluster);

//----------
int			get_end_i(int start_i, int start_j, t_boards *boards);
int			get_end_j(int start_i, int start_j, t_boards *boards);
int			count_tiles(char **board);
void		set_board_grav_values(t_cluster *cluster);
void		alloc_board_tiles_falling(t_cluster *cluster, int tile_count);

void		animation_setup(t_cluster *cluster);
uint32_t	get_color_buffer(int32_t x, int32_t y, uint8_t *pixels);
void		draw_rotation(t_cluster *cluster);
void		free_grav_tiles(t_cluster *cluster);
#endif
