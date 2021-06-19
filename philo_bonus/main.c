/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:51:41 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 19:26:17 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_state *state)
{
	sem_unlink(PHILO_SEM);
	sem_unlink(MAIN_SEM);
	sem_unlink(PRINT_SEM);
	state->forks = sem_open(PHILO_SEM, O_CREAT
			| O_EXCL, 0644, state->philosophers);
	state->main_sem = sem_open(MAIN_SEM, O_CREAT
			| O_EXCL, 0644, 0);
	state->print_sem = sem_open(PRINT_SEM, O_CREAT
			| O_EXCL, 0644, 1);
	state->start_time = get_time();
	if (!state->forks || !state->main_sem
		|| !state->print_sem || !state->start_time)
		printf("error : sem_open()\n");
}

void	free_state(t_philo **philos)
{
	int	i;

	i = 0;
	sem_unlink(PRINT_SEM);
	sem_unlink(MAIN_SEM);
	sem_unlink(PHILO_SEM);
	free((*philos)->state);
	free((*philos));
}

int	main(int c, char **argv)
{
	t_state	*state;
	t_philo	*philos;
	int		i;

	i = 0;
	state = (t_state *)malloc(sizeof(t_state));
	if (!parsing(c, argv, state))
		exit (0);
	init_semaphores(state);
	philos = (t_philo *)malloc(sizeof(t_philo) * state->philosophers);
	init_philos(&philos, state);
	while (i < state->philosophers)
	{
		philos[i].id = fork();
		if (philos[i].id == 0)
			routine(&philos[i]);
		i++;
	}
	sem_wait(state->main_sem);
	i = -1;
	while (++i < state->philosophers)
		kill(philos[i].id, SIGKILL);
	free_state(&philos);
	return (0);
}
