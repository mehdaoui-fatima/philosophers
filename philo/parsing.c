/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:05:43 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 20:16:44 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_values(int *args, int c, t_state *state)
{
	state->philosophers = args[0];
	state->time_to_die = args[1];
	state->time_to_eat = args[2];
	state->time_to_sleep = args[3];
	if (c == 6)
		state->must_eat = args[4];
	else
		state->must_eat = -1;
}

int	valid_input(int	*args, int c)
{
	if (!ft_ispositive(args, c - 1) || (args[0] < 1 || args[0] > 200)
		|| (args[1] < 60 || args[2] < 60 || args[3] < 60))
	{
		printf(FALSE_VALUES);
		return (0);
	}
	return (1);
}

int	parsing(int c, char **argv, t_state *state)
{
	int	*args;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (c < 5 || c > 6)
		printf(MANY_ARGS);
	else if (!is_digits(argv, c))
		printf(FALSE_TYPE);
	else
	{
		args = malloc(sizeof(int) * c - 1);
		while (++i < c)
			args[j++] = ft_atoi(argv[i]);
		if (!valid_input(args, c))
		{
			free(args);
			return (0);
		}
		get_values(args, c, state);
		free(args);
		return (1);
	}
	return (0);
}
