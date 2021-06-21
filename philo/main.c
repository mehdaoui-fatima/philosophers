/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 10:58:35 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/21 11:00:03 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int c, char **argv)
{
	t_philo	*philo;
	t_state	*state;

	state = (t_state *)malloc(sizeof(t_state));
	if (!parsing(c, argv, state))
	{
		free(state);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * state->philosophers);
	state_init(state);
	philo_init(philo, state);
	state->start_time = get_time();
	philo_create(philo, state);
	pthread_mutex_lock(&state->simulation);
	return (0);
}
