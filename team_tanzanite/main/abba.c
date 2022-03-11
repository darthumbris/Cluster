/*   Updated: 2022/03/07 18:17:25 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);



/*	
	t_parse parse;
	(...)
	if (parse.input == rotation)
	{
		// Do stuff with parse.data.rotation
	}
	else if (parse.input == column)
	{
		// Colour is in parse.data.column_data.colour
		// Column is in parse.data.column_data.colomn
	}

	//column colour 22 11
	//rotate 1-5 -1--5
*/

void	ft_error(char *error)
{
	printf("%s\n", error);
}

int	check_len(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return i;
}

void	free_array(char **input)
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

bool	is_valid_input(char *str, t_parse *parse)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]) && str[i] != '\n')
		{
			parse->input = invalid;
			return false;
		}
		i++;
	}
	return true;
}

// void	get_input(t_parse *parse, char **input, int argc)
// {
// 	if (argc == 2)
// 	{
// 		parse->data.rotation = atoi(input[1]);
// 		return ;
// 	}
// 	parse->data.column_data.colour = atoi(input[1]);
// 	parse->data.column_data.column = atoi(input[2]);
// }

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

int	main(void)
{
	t_parse	parse;
	char	**output;
	size_t size = 34;
	int fd;
	char	*input = NULL;

	while (getline(&input, &size, stdin))
	{
		output = ft_split(input, ' ');
		if (!output)
			return 1;
		if (strcmp(output[0], "rotate") == 0 && check_len(output) == 2)
		{
			if (is_valid_input(output[1], &parse))
			{
				parse.data.rotation = atoi(output[1]);
				parse.input = rotation;
			}
		}
		else if(strcmp(output[0], "column") == 0 && check_len(output) == 3)
		{
			if (is_valid_input(output[1], &parse) && is_valid_input(output[2], &parse))
			{
				parse.data.column_data.colour = atoi(output[1]);
				parse.data.column_data.column = atoi(output[2]);
				parse.input = column;
			}
		}
		else
			parse.input = invalid;
		check_input(&parse);
		if (parse.input == invalid)
			ft_error("invalid input\n");
		else
			printf("amazing\n");
	}	
	free(input);
	if (output)
		free_array(output);
	return (0);
}