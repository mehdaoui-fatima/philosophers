#include "philo_one.h"

void    philo_init_state(t_philo *philo, t_state *state)
{
    int i;
    int n;

    i = 0;
    
    n = state->number_of_philosophers;
    while (i < n)
    {
        philo[i].id = i + 1;
        philo[i].state = state;
        philo[i].last_meal = 0;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % n;
        printf("philo %d|left_fork %d|right_fork %d \n",i , philo[i].left_fork, philo[i].right_fork);
        i++;
    }
}

uint64_t get_time()//millisec
{   
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    *eat(void *philo)
{
    t_philo *arg;
    
    arg = (t_philo*)philo;
    pthread_mutex_lock(&(arg->state->forks[arg->right_fork]));
    printf("thread %d has taken right_fork %d\n",arg->id, arg->right_fork);
    pthread_mutex_lock(&(arg->state->forks[arg->left_fork]));
    printf("thread %d has taken left_fork %d\n",arg->id, arg->left_fork);
    printf("%llu|",get_time() - arg->state->start_time);
    printf("thread %d is eating \n",(arg->id));
    usleep(arg->state->time_to_eat * 1000);

    printf("thread %d has left right_fork %d and left_fork %d\n",arg->id, arg->right_fork, arg->left_fork);
    pthread_mutex_unlock(&(arg->state->forks[arg->right_fork]));
    pthread_mutex_unlock(&(arg->state->forks[arg->left_fork]));
    return NULL;
}



int main(int c, char **argv)
{
    t_philo *philo;
    t_state *state;
    int i;

    
    i = 0;
    state = (t_state*)malloc(sizeof(t_state));
    parsing(c, argv, state);
    philo = malloc(sizeof(t_philo) * state->number_of_philosophers);
    pthread_mutex_init(&(state->mutex), NULL);
    state->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) *  state->number_of_philosophers);
    for(int i = 0; i < state->number_of_philosophers; i++)
        pthread_mutex_init(&(state->forks[i]), NULL);
    printf("from main\n");
    philo_init_state(philo, state);
    state->start_time = get_time();
    while(i < state->number_of_philosophers)
    {
       if (pthread_create(&philo[i].pthread_id , NULL, eat, (void*)&philo[i]))
        {
            ft_putstr("pthread_create() error");
            exit (1);
        }
        i++;
    }
    sleep(2);
    ft_putstr("from main...\n");
}






































