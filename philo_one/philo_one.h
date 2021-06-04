#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<limits.h>


typedef struct s_philo {
    
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;


}   t_philo;

#endif

