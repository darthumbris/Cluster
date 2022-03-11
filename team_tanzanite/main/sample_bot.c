/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sample_bot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 18:06:00 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "defines.h"
#include "parsing.h"
#include <time.h>
#include <stddef.h>

static size_t	count_split(char	**split)
{
	size_t	count = 0;

	while (split[count++]);
	return (count - 1);
}

int	main(int argc, char **argv)
{
	int		in = 0;
	int		out = 0;
	char	*where = NULL;
	char	**colours_str;
	char	*line = NULL;
	int		*colours_num;
	size_t	len;

	srand(time(NULL));
	if (argc != 3)
	{
		printf("Usage: ./bot IN_FIFO OUT_FIFO\n");
		exit (1);
	}
	in = open(argv[1], O_ASYNC | O_NONBLOCK);
	if (in < 0)
		perror("Error");
	while (1)
	{
		line = get_next_line(in);
		if (line)
		{
			if (strstr(line, "won!"))
			{
				if (strstr(line, "(you)"))
					printf("I won!\n");
				else
					printf("I lost!\n");
				break ;
			}
			// Our turn, let's make a move!
			if (strstr(line, "(you)"))
			{
				where = strstr(line, "colors: ");
				colours_str = ft_split(where, ' ');
				if (!colours_str)
					break ;
				len = count_split(colours_str);
				colours_num = malloc(len * sizeof(int));
				for (size_t i = 0; i < len; i++)
					colours_num[i] = atoi(colours_str[i]);
				for (int i = 0; colours_str[i]; i++)
				{
					free(colours_str[i]);
				}
				free(colours_str);
				if (out)
				{
					close(out);
					out = 0;
				}
				out = open(argv[2], O_WRONLY | O_NONBLOCK, 0600);
				if (out < 0)
				{
					perror("Error");
					break ;
				}
				if (len)
				{
					//See if we're doing a rotation or a place move
					if (!(rand() % 4))
						dprintf(out, "rotate %d\n", (rand() % 5) + 1);
					else
						dprintf(out, "column %d %d\n", (rand() % TOTAL_COLUMNS) - g_options.board_width + 1,
							colours_num[rand() % len]);
				}
				//We drew no tokens, so we wait for the game's verdict.
				else
					continue ;
			}
		}
		free(line);
	}
	free(line);
	return (0);
}
