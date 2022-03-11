/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 15:56:08 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 19:47:22 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "defines.h"
# include <stdint.h>

typedef struct s_boards {
	char	**board_a;
	char	**board_b;
	char	which;
	int		start_x;
	int		start_y;
	int		end_y;
	int		end_x;
	int		*grav_start_x;
	int		*grav_start_y;
	int		*grav_end_x;
	int		*grav_end_y;
	int		*fallen;
	uint32_t	*grav_color;
	uint32_t	color;
}				t_boards;

t_boards	*initialize(void);
char		**init_board(void);
void		clear_board(char **board);
void		clear_boards(t_boards *boards);

#endif
