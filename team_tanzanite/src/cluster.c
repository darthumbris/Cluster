/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cluster.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:04:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/11 10:49:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

void	cluster_clear_screen(mlx_image_t *img, int color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	cluster_clean(t_cluster *cluster)
{
	if (cluster == NULL)
		return ;
	if (cluster->boards)
		clear_boards(cluster->boards);
	if (cluster->lclick_icon)
	{
		free(cluster->lclick_icon->pixels);
		free(cluster->lclick_icon);
	}
	if (cluster->rclick_icon)
	{
		free(cluster->rclick_icon->pixels);
		free(cluster->rclick_icon);
	}
	if (cluster->mlx && cluster->bgbuffer)
	{
		mlx_delete_image(cluster->mlx, cluster->bgbuffer);
		free(cluster->bgbuffer);
	}
	if (cluster->mlx && cluster->buffer)
	{
		mlx_delete_image(cluster->mlx, cluster->buffer);
		free(cluster->buffer);
	}
	if (cluster->mlx)
		mlx_terminate(cluster->mlx);
	clear_board(cluster->animation_board);
	free(cluster);
	cluster = NULL;
}

static void	_set_time(t_cluster *cluster)
{
	gettimeofday(&(cluster->next_play), NULL);
	cluster->next_play.tv_usec += g_options.delay_us;
	while (cluster->next_play.tv_usec >= 1000000)
	{
		(cluster->next_play.tv_usec) -= 1000000;
		(cluster->next_play.tv_sec)++;
	}
}

/* TODO: Closing of the descriptors? */
static void	_player_io(t_cluster *cluster)
{
	cluster->player[0].io[0] = open(P1_IN, O_NONBLOCK | O_ASYNC);
	if (BOTS)
		cluster->player[0].io[1] = open(P1_OUT, O_NONBLOCK | O_WRONLY | O_APPEND, 0600);
	cluster->player[0].io[2] = open(P1_IN, O_NONBLOCK | O_WRONLY | O_APPEND, 0600);
//	cluster->player[0].io[2] = open("log.log", O_CREAT | O_WRONLY | O_APPEND, 0600);
	cluster->player[1].io[0] = open(P2_IN, O_NONBLOCK | O_ASYNC);
	if (BOTS)
		cluster->player[1].io[1] = open(P2_OUT, O_NONBLOCK | O_WRONLY | O_APPEND, 0600);
	cluster->player[1].io[2] = open(P2_IN, O_NONBLOCK | O_WRONLY | O_APPEND, 0600);
	if (cluster->player[0].io[0] < 0 || cluster->player[1].io[0] < 0
		|| cluster->player[0].io[1] < 0 || cluster->player[1].io[1] < 0
		|| cluster->player[0].io[2] < 0 || cluster->player[1].io[2] < 0)
	{
		perror("Error");
		cluster_clean(cluster);
	}
	cluster->player[0].how_verbose = 1;
	cluster->player[1].how_verbose = 1;
}

t_cluster	*cluster_init(int w, int h, const char *title)
{
	t_cluster	*cluster;

	cluster = calloc(1, sizeof(t_cluster));
	if (cluster == NULL)
		return (NULL);
	cluster->mlx = mlx_init(w, h, title, SCREEN_RESIZE);
	if (cluster->mlx == NULL)
	{
		free(cluster);
		return (NULL);
	}
	cluster->bgbuffer = mlx_new_image(cluster->mlx, w, h);
	if (cluster->bgbuffer == NULL)
	{
		cluster_clean(cluster);
		return (NULL);
	}
	cluster->lclick_icon = mlx_load_png("assets/left_click_icon_b.png");
	if (cluster->lclick_icon == NULL)
	{
		cluster_clean(cluster);
		return (NULL);
	}
	cluster->rclick_icon = mlx_load_png("assets/right_click_icon_b.png");
	if (cluster->rclick_icon == NULL)
	{
		cluster_clean(cluster);
		return (NULL);
	}
	mlx_image_to_window(cluster->mlx, cluster->bgbuffer, 0, 0);
	cluster->buffer = mlx_new_image(cluster->mlx, w, h);
	if (cluster->buffer == NULL)
	{
		cluster_clean(cluster);
		return (NULL);
	}
	mlx_image_to_window(cluster->mlx, cluster->buffer, 0, 0);
	cluster_clear_screen(cluster->bgbuffer, BACKGROUND_COLOR);
	_set_time(cluster);
	_player_io(cluster);
	cluster->col_anim = false;
	cluster->grav_anim = false;
	cluster->rot_anim = false;
	cluster->angle = 0;
	cluster->angle_end = 0;
	return (cluster);
}

void	cluster_close(void *arg)
{
	t_cluster	*cluster;

	cluster = (t_cluster *)arg;
	mlx_close_window(cluster->mlx);
}

void	cluster_loop(void *arg)
{
	loop_run((t_cluster *)arg);
}

void	cluster_hooks(t_cluster *cluster)
{
	mlx_close_hook(cluster->mlx, cluster_close, cluster);
	mlx_loop_hook(cluster->mlx, cluster_loop, cluster);
}
