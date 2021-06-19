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
# define MANY_ARGS		"Error: Incorrect number of arguments\n"
# define FALSE_VALUES	"Error: Incorrect values\n"
# define FALSE_TYPE		"Error: Arguments should be numbers, not strings\n"
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
void    print_args(int *args, int j);
int					parsing(int c, char **argv, t_state *state);
int					check_digit(char *s);
int					is_digits(char **argv, int c);

#endif

