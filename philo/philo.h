#ifndef PHILO_H
#define PHILO_H

#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>
#include <sys/time.h>

#define RED_ "\x1B[31m" 
#define NRM_ "\x1B[0m"

#define MANY_ARGS    "Error: Too many arguments NRM_"
#define INSU_ARGS    "Error: Insufficient number of arguments " 
#define POS_VALUES   "Error: Arguments should be positive "
#define FALSE_VALUES "Error : Number of philosophers should be in rang [1..200] "
#define FALSE_TIME   "Error: time_to_[die, eat, sleep, each_must_eat] should not be under 60ms "
#define forking "has take a fork"
#define eating "is eating"
#define sleeping "is sleeping"
#define died "died"


typedef struct s_state {

	int philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat;
	pthread_mutex_t mutex;
	uint64_t start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t simulation;
	pthread_mutex_t print_mutex;
	int	counter;

}               t_state;


typedef struct s_philo{
	
	int id;
	t_state *state;
	pthread_t pthread_id;
	unsigned long long die_t;
	int left_fork;
	int right_fork;
	int eat_number;
}               t_philo;



size_t	ft_strlen(const char *s);
int     ft_atoi(char *s);
int     ft_ispositive(int *s, int n);
void	ft_putstr(char *s);
void    print_args(int *args, int j);
void    parsing(int c, char **argv, t_state *state);


#endif
