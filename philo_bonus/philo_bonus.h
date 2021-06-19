/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:29:44 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 20:08:45 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <limits.h>
# include <semaphore.h>
# include <sys/time.h>
# include <errno.h>
# define PHILO_SEM		"/forks_sem"
# define MAIN_SEM		"/main_sem"
# define PRINT_SEM		"/print_sem"
# define EAT_SEM		"/eat_sem"
# define MANY_ARGS		"Error: Incorrect number of arguments\n"
# define FALSE_VALUES	"Error: Incorrect values\n"
# define FALSE_TYPE		"Error: Arguments should be numbers, not strings\n"
# define FORKING		"has take a fork"
# define EATING			"is eating"
# define SLEEPING		"is sleeping"
# define DIED			"died"
# define THINKING		"is thinking"

typedef struct s_state {
	int					philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	unsigned long long	start_time;
	sem_t				*forks;
	sem_t				*main_sem;
	sem_t				*print_sem;
	pthread_t			die_thread;
	pthread_t			eat_thread;
}						t_state;

typedef struct s_philo{
	pid_t				id;
	t_state				*state;
	int					index;
	int					die_t;
	sem_t				*eat_sem;
}						t_philo;

size_t				ft_strlen(const char *s);
int					ft_atoi(char *s);
int					ft_ispositive(int *s, int n);
int					check_digit(char *s);
int					is_digits(char **argv, int c);
int					parsing(int c, char **argv, t_state *state);
void				eat(t_philo *philo);
void				_sleep(t_philo *philo);
void				*check_die(void *philo);
void				*check_eat(void *philos);
void				routine(t_philo *philo);
unsigned long long	get_time(void);
void				print(t_philo *philo, char *s);
char				*ft_strjoin(char *str, int index);
void				init_philos(t_philo **philos, t_state *state);

#endif