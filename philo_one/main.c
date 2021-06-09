#include "philo_one.h"

uint64_t get_time()//millisec
{   
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    philo_init_state(t_philo *philo, t_state *s)
{
    int i;
    int n;

    i = 0;
    
    n = s->number_of_philosophers;
    while (i < n)
    {
        philo[i].id = i + 1;
        philo[i].s = s;
        philo[i].t_meal = 0;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % n;
        printf("philo %d|left_fork %d|right_fork %d \n",i , philo[i].left_fork, philo[i].right_fork);
        i++;
    }
}




void    *eat(void *philo)
{
    t_philo *p;
    long long btw;
    
    p = (t_philo*)philo;
    pthread_mutex_lock(&(p->s->forks[p->right_fork]));
    printf("%llu thread %d has taken right_fork %d\n",(get_time() - p->s->start_time), p->id, p->right_fork);
    pthread_mutex_lock(&(p->s->forks[p->left_fork]));
    printf("%llu thread %d has taken left_fork %d\n",(get_time() - p->s->start_time), p->id, p->left_fork);
    if((get_time() - p->s->start_time) > (p->t_meal + p->s->time_to_die))
    {
        printf("%llu|%llu|should die %d \n",get_time() - p->s->start_time , p->t_meal + p->s->time_to_die, p->id);
        pthread_mutex_unlock(&p->s->simulation);
        exit(1);
    }
    p->t_meal = get_time() - p->s->start_time; //ms
    printf("%llu|%llu|thread %d\n",get_time() - p->s->start_time, p->t_meal, p->id);
    printf("%llu thread %d is eating \n",(get_time() - p->s->start_time), (p->id));
    usleep(p->s->time_to_eat * 1000);
    printf("%llu thread %d has left right_fork %d and left_fork %d\n",(get_time() - p->s->start_time), p->id, p->right_fork, p->left_fork);
    pthread_mutex_unlock(&(p->s->forks[p->right_fork]));
    pthread_mutex_unlock(&(p->s->forks[p->left_fork]));
    return NULL;
}



//may be e scrambled or intertwined 
void    _sleep(void *philo)
{
    t_philo *p;

    p = (t_philo*)philo;
    printf("%llu thread %d is sleeping \n",(get_time() - p->s->start_time),p->id);
    usleep(p->s->time_to_sleep * 1000);
}

void    *think(void *philo)
{
    t_philo *p;

    p = (t_philo*)p;
    printf("thread %d is thinking\n", p->id);
    return NULL;
}

void    *routine(void  *philo)
{
    while (1)
    {
        eat(philo);
        _sleep(philo);
        think(philo);
    }
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
    // lock simulation so main lock a mutex before executing all coming instructions
    pthread_mutex_init(&state->simulation, NULL);
    pthread_mutex_lock(&state->simulation);
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
       if (pthread_create(&philo[i].pthread_id , NULL, routine, (void*)&philo[i]))
        {
            ft_putstr("pthread_create() error");
            exit (1);
        }
        i++;
    }
    // sleep(2);
    /* lock simulation() will let principal thread stack because the simulation mutex he tried to lock already locked,
     main will continue until simulation unlocked by another tried in case of death of one of philosophers*/
    pthread_mutex_lock(&state->simulation);
    pthread_mutex_unlock(&state->simulation);
    ft_putstr("from main...\n");
}






































