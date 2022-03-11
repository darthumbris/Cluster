#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdbool.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include "defines.h"
# include "split.h"
# include "get_next_line.h"
# define MAX_COLUMN (g_options.board_width - 1)
# define  MIN_COLUMN (-MAX_COLUMN)

typedef struct s_column_data
{
	int	column;
	int	colour;
}		t_column_data;

typedef union u_data
{
	t_column_data	column_data;
	int 				rotation;
	int				how_verbose;
}					t_data;

typedef enum e_input
{
	invalid,
	rotation,
	column,
	verbosity
}	t_input;

typedef struct s_parse
{
	t_input			input;
	t_data			data;
}					t_parse;

bool	get_input(t_parse *parse, int io);

#endif
