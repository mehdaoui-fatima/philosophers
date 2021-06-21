/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:27:50 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/21 11:30:25 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>
# define RED_ "\x1B[31m" 
# define NRM_ "\x1B[0m"
# define MANY_ARGS		"Error: Incorrect number of arguments\n"
# define FALSE_VALUES	"Error: Incorrect values\n"
# define FALSE_TYPE		"Error: Arguments should be numbers, not strings\n"
# define FORKING		"has take a fork"
# define EATING			"is eating"
# define THINKING		"is thinking"
# define SLEEPING 		"is sleeping"
# define DIED			"died"

typedef struct s_state {
	int					philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	pthread_mutex_t		mutex;
	uint64_t			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		simulation;
	pthread_mutex_t		print_mutex;
	int					counter;
}						t_state;

typedef struct s_philo {
	int					id;
	t_state				*state;
	pthread_t			pthread_id;
	unsigned long long	die_t;
	int					left_fork;
	int					right_fork;
	int					eat_number;
}						t_philo;

uint64_t				get_time(void);
void					print(t_philo *philo, char *task_type);
void					philo_init(t_philo *philo, t_state *state);
void					state_init(t_state *state);
void					philo_create(t_philo *philo, t_state *state);
void					get_values(int *args, int c, t_state *state);
int						valid_input(int	*args, int c);
int						parsing(int c, char **argv, t_state *state);
size_t					ft_strlen(const char *s);
int						ft_atoi(char *s);
int						ft_ispositive(int *s, int n);
int						check_digit(char *s);
int						is_digits(char **argv, int c);
void					*routine(void *philo);
void					*check_die(void *philo);
void					_sleep(void *philo);
void					*eat(void *philo);
void					*think(void *philo);

#endif
