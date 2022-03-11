#include "parsing.h"
#include <stdio.h>

bool	is_valid_input(char *str, t_parse *parse)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] != '\n' && !isdigit(str[i]))
		{
			parse->input = invalid;
			return false;
		}
		i++;
	}
	return true;
}

int	check_len(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return i;
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

void	check_input(t_parse *parse)
{
	if (parse->input == rotation)
	{
		if (parse->data.rotation < -5 || parse->data.rotation > 5)
			parse->input = invalid;
		else
		{
			if (parse->data.rotation < 0)
				parse->data.rotation += 6;
		}
	}
	else if (parse->input == column)
	{
		if (parse->data.column_data.column < MIN_COLUMN || parse->data.column_data.column > MAX_COLUMN)
			parse->input = invalid;
	}
}

//	TODO: Cleanup
bool	get_input(t_parse *parse, int io)
{
    char	*line = NULL;
    char    **output;

    line = get_next_line(io);
    if (!line)
       return false;
    if (strlen(line) == 0)
    {
        free(line);
        return false;
    }
    output = ft_split(line, ' ');
    if (!output)
    {
        free(line);
        return false;
    }
    if (strcmp(output[0], "rotate") == 0 && check_len(output) == 2)
	{
			if (is_valid_input(output[1], parse))
			{
				parse->data.rotation = atoi(output[1]);
				parse->input = rotation;
			}
	}
    else if (strcmp(output[0], "verbosity") == 0 && check_len(output) == 2)
	{
			if (is_valid_input(output[1], parse))
			{
				parse->data.how_verbose = atoi(output[1]);
				parse->input = verbosity;
			}
	}
    else if(strcmp(output[0], "column") == 0 && check_len(output) == 3)
    {
        if (is_valid_input(output[1], parse) && is_valid_input(output[2], parse))
        {
            parse->data.column_data.colour = atoi(output[2]);
            parse->data.column_data.column = atoi(output[1]);
            parse->input = column;
        }
    }
    else
	{
        parse->input = invalid;
	}
	check_input(parse);
	free_array(output);
	free(line);
    return true;

}
