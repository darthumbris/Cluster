/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shuffle.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:06:47 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/03/08 14:16:40 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include <stdlib.h>
#include <time.h>

static void	swapc(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	shuffle_array(char *array, int n)
{
	int	i;
	int	r_index;

	srand(time(NULL));
	i = n - 1;

	while (i > 0)
	{
		r_index = rand() % (i + 1);
		swapc(&array[i], &array[r_index]);
		i--;
	}
}
