/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:13:17 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 20:12:15 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print(t_philo *philo, char *s)
{
	sem_wait(philo->state->print_sem);
	printf("%llu %d %s\n", get_time()
		- philo->state->start_time, philo->index, s);
	sem_post(philo->state->print_sem);
}

char	*ft_strjoin(char *str, int index)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
	while (i < ft_strlen(str))
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i++] = index + '0';
	newstr[i] = '\0';
	return (newstr);
}

void	init_philos(t_philo **philos, t_state *state)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < state->philosophers)
	{
		(*philos)[i].state = state;
		(*philos)[i].index = i + 1;
		if (state->time_to_eat != -1)
		{
			tmp = ft_strjoin(EAT_SEM, i);
			sem_unlink(tmp);
			(*philos)[i].eat_sem = sem_open(tmp, O_CREAT | O_EXCL, 0644, 0);
			free(tmp);
		}
		i++;
	}
	if (state->must_eat != -1)
		pthread_create(&(*philos)->state->eat_thread,
			NULL, check_eat, (void *)(*philos));
}
