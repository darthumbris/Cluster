#include "global.h"
#include <stddef.h>
#include <stdio.h>
#include "split.h"
#include "get_next_line.h"
#include "defines.h"

t_option	g_options =
{
	.players = 2,
	.board_width = 5,
	.delay_us = 5000,
	.screen_width = 800,
	.screen_height = 800,
	.colors_to_play = 2,
	.color_amount_per_turn = 2,
	.color_sets_in_bag = 12,
	.enable_animation = 1,
	.enable_ui = 1,
	.enable_grid = 1,
	.in_a_row = 4
};

int	*get_value(char *output)
{
	int							i;
	static const t_lookup		table[] =
	{
		{"players", &g_options.players},
		{"board_width", &g_options.board_width},
		{"delay_us", &g_options.delay_us},
		{"screen_width", &g_options.screen_width},
		{"screen_height", &g_options.screen_height},
		{"colors_to_play", &g_options.colors_to_play},
		{"color_amount_per_turn", &g_options.color_amount_per_turn},
		{"color_sets_in_bag", &g_options.color_sets_in_bag},
		{"enable_animation", &g_options.enable_animation},
		{"enable_ui", &g_options.enable_ui},
		{"enable_grid", &g_options.enable_grid},
		{"in_a_row", &g_options.in_a_row},
		{NULL, NULL}
	};

	i = 0;
	while (table[i].str != NULL)
	{
		if (!strcmp(output, table[i].str))
		{
				return table[i].value;
		}
		i++;
	}
	return (NULL);
}

static void	fix_color_sets_in_bag(void)
{
	int *color_sets_in_bag;
	int	total_columns;

	color_sets_in_bag = get_value("color_sets_in_bag");
	total_columns = (g_options.board_width * 2) - 1;
	(*color_sets_in_bag) = (((total_columns * total_columns) - ((g_options.board_width) - 1)
		* g_options.board_width) / (g_options.colors_to_play * g_options.players));
}

static void	free_array(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
}

static char	*remove_spaces(char *str)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	return (str);
}


static void	sanitize_global(void)
{
	g_options.players = 2;
	if (g_options.board_width < 1 || g_options.board_width > 256)
		g_options.board_width = 5; //to change with the correct number
	if (g_options.delay_us < 0 || g_options.delay_us > 1000000) 
		g_options.delay_us = 500000;
	if (g_options.screen_width < 0 || g_options.screen_width > 2048)
		g_options.screen_width = 1024;
	if (g_options.screen_height < 0 || g_options.screen_height > 2048)
		g_options.screen_height = 1024;
	if (g_options.colors_to_play % 2 == 1 || g_options.colors_to_play < 2)
		g_options.colors_to_play = 2;
	if (g_options.color_amount_per_turn < 1)
		g_options.color_amount_per_turn = 2;
	if (g_options.color_sets_in_bag < 1)
		g_options.color_sets_in_bag = 40;
}

void	gobal_settings(char *file)
{
	char		*str;
	int			fd;
	char		**output;
	int			*value;

	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		perror("bad fd");
		return ;
	}
	while ((str = get_next_line(fd)))
	{
		str = remove_spaces(str);
		output = ft_split(str, '=');
		value = get_value(output[0]);
		if (value)
			*value = atoi(output[1]);
		free(str);
		free_array(output);
	}
	sanitize_global();
	fix_color_sets_in_bag();
}
