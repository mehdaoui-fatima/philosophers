/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 08:21:52 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/21 11:17:37 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo *philo, char *task_type)
{
	pthread_mutex_lock(&philo->state->print_mutex);
	printf("%llu thread %d %s\n",
		(get_time() - philo->state->start_time), philo->id, task_type);
	pthread_mutex_unlock(&philo->state->print_mutex);
}

void	philo_init(t_philo *philo, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philosophers)
	{
		philo[i].id = i + 1;
		philo[i].state = state;
		philo[i].die_t = 0;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % state->philosophers;
		philo[i].eat_number = 0;
		i++;
	}
}

void	state_init(t_state *state)
{
	int	i;

	i = 0;
	pthread_mutex_init(&state->simulation, NULL);
	pthread_mutex_init(&state->print_mutex, NULL);
	pthread_mutex_lock(&state->simulation);
	state->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * state->philosophers);
	while (i < state->philosophers)
	{
		pthread_mutex_init(&(state->forks[i]), NULL);
		i++;
	}
}

void	philo_create(t_philo *philo, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->philosophers)
	{
		if (pthread_create(&philo[i].pthread_id,
				NULL, routine, (void *)&philo[i]))
		{
			printf("pthread_create() error");
			return ;
		}
		i++;
		usleep(100);
	}
}
