/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cluster.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:55:58 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/11 10:26:50 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_H
# define CLUSTER_H

# include "defines.h"

/* Full path to the MLX42 header */
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "initialize.h"
# include "parsing.h"
# include "global.h"

# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

// This line causes a linker error on Linux
// struct timeval timestruct;

/**
**	gamestate represents in what state the program is currently in
*/
typedef enum e_gamestate
{
	STATE_INITIALIZATION = 0,
	STATE_HANDLE_INPUT,
	STATE_DRAWING,
	STATE_OUTPUT,
	STATE_ANIMATION,
	STATE_END
}	t_gamestate;

/**
**	TODO: Add params
**	Represents a player
**	@param index <int> the index of the player (1v1 means either 0 or 1)
**	@param amount_left <int> Amount of tokens still in the color bag
**	@param token_colors <uchar*> which colors does this player play
**	@param tokens_in_hand	<uchar*> which colors has the players taken from bag
**	@param token_bag <uchar*> The bag of colors
*/
typedef struct s_player
{
	int				index;
	int				amount_left;
	unsigned char	token_colors[MAX_COLORS];
	unsigned char	tokens_in_hand[MAX_TOKENS_IN_HAND];
	unsigned char	token_bag[MAX_BAG_SIZE];
	int				how_verbose;
	int				io[3];
}					t_player;

/**
**	TODO: Add params
**	Cluster struct that holds mlx data
**	@param mlx <mlx_t*> mlx struct pointer (gotten from mlx_init)
**	@param buffer <mlx_image_t*> image for the entire screen
**	@param boards <t_boards*> pointer to the boards
**	@param player <t_player*> Players
*/
typedef struct s_cluster
{
	t_gamestate		state;
	mlx_t			*mlx;
	mlx_image_t		*buffer;
	mlx_image_t		*bgbuffer;
	mlx_texture_t	*lclick_icon;
	mlx_texture_t	*rclick_icon;
	mlx_texture_t	*mclick_icon;
	t_boards		*boards;
	t_parse			current_move;
	t_player		player[2];
	struct timeval	next_play;
	int				active_player;
	bool			col_anim;
	bool			grav_anim;
	bool			rot_anim;
	double			angle;
	double			angle_end;
	int				total_rotations;
	int				current_rotation;
	char			**animation_board;
	bool			mouse_held_down;
	int				drag_color;
	mlx_image_t		*win_msg;
}				t_cluster;

/* cluster.c */
t_cluster	*cluster_init(int w, int h, const char *title);
void		cluster_hooks(t_cluster *cluster);
void		cluster_close(void *arg);
void		cluster_clean(t_cluster *cluster);
void		cluster_clear_screen(mlx_image_t *img, int color);

/* loop.c */
void		loop_run(t_cluster *cluster);

/* players.c */
bool		player_is_bag_empty(t_player *player);
void		player_add_token(t_player *player, int token);
int			player_take_token(t_player *player);
bool		player_has_playcolor(t_player *player, int c);
void		player_set_playcolors(t_player *player);
void		player_fill_bag(t_player *player);
void		player_tokens_to_hand(t_player *player);
void		player_bag_shuffle(t_player *player);

/* shuffle.c */
void		shuffle_array(char *array, int n);

/* boardstate.c */
char		*boardstate_to_raw(char **board, int size);
char		**boardstate_from_raw(char *raw, int w, int h);

/* input.c */
int			mouse_x_to_column(int x);
void		mouse_input_stuff(t_cluster *cluster);

bool		is_valid_move(t_parse *move, t_player *player);


/* output.c */
void		output(t_cluster *cluster);
void		output_announce_winner(t_cluster *cluster, t_player *winner);
void		output_bots(t_cluster *cluster);

/* GRAPHICS */

void		draw_board(char **board, mlx_image_t *img, bool empty);
void		draw_hexagon(int row, int col, uint32_t color, mlx_image_t *img, float hex_height);
float		get_hex_width(int height);
void		draw_grid(mlx_image_t *img);
void		draw_hexagon_outline(int row, int col, mlx_image_t *img, float hex_height);
void		draw_ui(t_cluster *cluster, int to_highlight);
float		get_hex_height(void);
uint32_t	get_color(int i);
void		draw_gravity(t_cluster *cluster);
void		move_grav_positions(t_cluster *cluster);

#endif
