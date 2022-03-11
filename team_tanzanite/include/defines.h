/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 10:48:30 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/11 10:29:24 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define NO_BG_TILES false
# define ANIM_SPEED_MODIFIER 3

# include "global.h"

/* For the window */
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1400
# endif
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1400
# endif
# ifndef SCREEN_TITLE
#  define SCREEN_TITLE "Cluster"
# endif
# ifndef SCREEN_RESIZE
#  define SCREEN_RESIZE false
# endif

/* For the tokens */
# ifndef TOTAL_TOKENS
#  define TOTAL_TOKENS (g_options.color_sets_in_bag * g_options.colors_to_play)
# endif

# ifndef TOTAL_COLUMNS
#  define TOTAL_COLUMNS ((g_options.board_width * 2) - 1)
# endif

# define MAX_COLORS 1000
# define MAX_TOKENS_IN_HAND 100
# define MAX_BAG_SIZE 1000

/* file i/o */
# ifndef P1_IN
#  define P1_IN "p1_in"
# endif
# ifndef P2_IN
#  define P2_IN "p2_in"
# endif
# ifndef P1_OUT
#  define P1_OUT "p1_out"
# endif
# ifndef P2_OUT
#  define P2_OUT "p2_out"
# endif

/* human player timeouts */
# ifndef DELAY_US
#  define DELAY_US 0
# endif

/* hex stuff */
# ifndef BACKGROUND_COLOR
#  define BACKGROUND_COLOR 0x000000FF
# endif
# ifndef HEX_OUTLINE_COLOR
#  define HEX_OUTLINE_COLOR 0xAAAAAAFF
# endif
# ifndef WHITE
#  define WHITE 0xffffffff
# endif
# ifndef ANGLE
#  define ANGLE 1.04719755
# endif
# ifndef HIGHLIGHT
#  define HIGHLIGHT 0xFF00FFFF
# endif
# ifndef TAN_ANGLE
#  define TAN_ANGLE 1.73205080278 //	tan() no longer needed
# endif
# define HEX_HEIGHT (g_options.screen_height / (2 * g_options.board_width + 2))

/* BOT-mode or not */
# ifndef BOTS
#  define BOTS false
# endif

enum e_which
{
	A,
	B
};

#endif
