/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:14:58 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 20:13:39 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->state->forks);
	print(philo, FORKING);
	sem_wait(philo->state->forks);
	print(philo, FORKING);
	philo->die_t = get_time()
		- philo->state->start_time + philo->state->time_to_die;
	print(philo, EATING);
	usleep(philo->state->time_to_eat * 1000);
	sem_post(philo->eat_sem);
	sem_post(philo->state->forks);
	sem_post(philo->state->forks);
}

void	_sleep(t_philo *philo)
{
	print(philo, SLEEPING);
	usleep(philo->state->time_to_sleep * 1000);
}

void	*check_die(void *philo)
{
	t_philo		*p;
	long long	died_t;

	p = (t_philo *)philo;
	while (1)
	{
		if ((get_time() - p->state->start_time) > p->die_t)
		{
			sem_wait(p->state->print_sem);
			printf("%llu %d died \n",
				   (get_time() - p->state->start_time), p->index);
			sem_post(p->state->main_sem);
			exit(0);
		}
		usleep (500);
	}
	return (NULL);
}

void	*check_eat(void *philos)
{
	t_philo	*p;
	int		i;
	int		nbr;

	nbr = 0;
	p = (t_philo *)philos;
	while (nbr < p->state->must_eat)
	{
		i = 0;
		while (i < p->state->philosophers)
			sem_wait(p[i++].eat_sem);
		nbr++;
	}
	sem_post(p[0].state->main_sem);
	return (NULL);
}

void	routine(t_philo *philo)
{
	philo->die_t = (get_time() - philo->state->start_time)
		+ philo->state->time_to_die;
	pthread_create(&philo->state->die_thread, NULL, check_die, (void *)philo);
	pthread_detach(philo->state->die_thread);
	while (1)
	{
		eat(philo);
		_sleep(philo);
		print(philo, THINKING);
	}
	exit (0);
}
