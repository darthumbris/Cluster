/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   translate.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rrinia <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 19:50:27 by rrinia        #+#    #+#                 */
/*   Updated: 2022/03/10 20:52:28 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <move.h>

t_coord translate(int column_number)
{
	t_coord	coord;

	coord.x = min((TOTAL_COLUMNS - 1), (TOTAL_COLUMNS - 1 - column_number));
	coord.y = min((TOTAL_COLUMNS - 1), (TOTAL_COLUMNS - 1 + column_number));
	return (coord);
}
