#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>
#define RED_ "\x1B[31m" 
#define NRM_ "\x1B[0m"

#define MANY_ARGS    "Error: Too many arguments NRM_"
#define INSU_ARGS    "Error: Insufficient number of arguments " 
#define POS_VALUES   "Error: Arguments should be positive "
#define FALSE_VALUES "Error : Number of philosophers should be in rang [2..200] "
#define FALSE_TIME   "Error: time_to_[die, eat, sleep, each_must_eat] should not be under 60ms "


typedef struct s_state {
    
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}   t_state;

size_t	ft_strlen(const char *s);
int     ft_atoi(char *s);
int     ft_ispositive(int *s, int n);
void	ft_putstr(char *s);
void    print_args(int *args, int j);
void    parsing(int c, char **argv, t_state *state);


#endif

