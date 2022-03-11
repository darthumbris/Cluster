#ifndef GLOBAL_H
# define GLOBAL_H

# include <fcntl.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_lookup
{
	char	*str;
	void	*value;
}			t_lookup;

typedef struct s_option
{
	int players;
	int board_width;
	int delay_us;
	int screen_width;
	int screen_height;
	int colors_to_play;
	int	color_amount_per_turn;
	int color_sets_in_bag;
	int enable_animation;
	int enable_ui;
	int enable_grid;
	int in_a_row;
}	t_option;

extern t_option	g_options;

void	gobal_settings(char *file);

#endif
