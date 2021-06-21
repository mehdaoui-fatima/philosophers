/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:01:41 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/21 11:22:51 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&(p->state->forks[p->left_fork]));
	print(philo, FORKING);
	pthread_mutex_lock(&(p->state->forks[p->right_fork]));
	print(philo, FORKING);
	p->die_t = get_time() - p->state->start_time + p->die_t;
	print(philo, EATING);
	usleep(p->state->time_to_eat * 1000);
	pthread_mutex_unlock(&(p->state->forks[p->right_fork]));
	pthread_mutex_unlock(&(p->state->forks[p->left_fork]));
	if (p->state->must_eat != -1)
		p->eat_number++;
	return (NULL);
}

void	_sleep(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	print(philo, SLEEPING);
	usleep(p->state->time_to_sleep * 1000);
}

void	*think(void *philo)
{
	t_philo	*p;

	p = (t_philo *)p;
	print(p, THINKING);
	return (NULL);
}

void	*check_die(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if ((get_time() - p->state->start_time) > p->die_t)
		{
			pthread_mutex_lock(&p->state->print_mutex);
			printf("\033[0;31m%llu\t%d\tdied\033[0m\n",
				get_time() - p->state->start_time, p->id);
			pthread_mutex_unlock(&p->state->simulation);
		}
		if (p->state->counter == p->state->philosophers)
		{
			pthread_mutex_lock(&p->state->print_mutex);
			printf("\033[0;31m%llu\t%d\tSimulation end\033[0m\n",
				get_time() - p->state->start_time, p->id);
			pthread_mutex_unlock(&p->state->simulation);
		}
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *philo)
{
	t_philo		*p;
	pthread_t	pthread_id;

	p = (t_philo *)philo;
	p->die_t = get_time() - p->state->start_time + p->state->time_to_die;
	pthread_create(&pthread_id, NULL, check_die, philo);
	while (1)
	{
		eat(philo);
		_sleep(philo);
		think(philo);
		if (p->eat_number == p->state->must_eat)
			p->state->counter++;
		if (p->state->counter == p->state->philosophers)
			break ;
	}
	return (NULL);
}
