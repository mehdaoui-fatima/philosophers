#include "philo.h"

uint64_t get_time()
{   
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void    print(t_philo *philo, char *task_type)
{
    pthread_mutex_lock(&philo->state->print_mutex);
    printf("%llu thread %d %s\n",(get_time() - philo->state->start_time), philo->id, task_type);
    pthread_mutex_unlock(&philo->state->print_mutex);
}

void    philo_init(t_philo *philo, t_state *state)
{
    int i;

    i = 0;
    while (i < state->philosophers)
    {
        philo[i].id = i + 1;
        philo[i].state = state;
        philo[i].die_t = 0;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % state->philosophers;
        philo[i].eat_number = 0;
        i++;
    }
}

void    state_init(t_state *state)
{
    int i;

    i = 0;
    pthread_mutex_init(&state->simulation, NULL);
    pthread_mutex_init(&state->print_mutex, NULL);
    pthread_mutex_lock(&state->simulation);
    state->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * state->philosophers);
    while(i < state->philosophers)
    {
        pthread_mutex_init(&(state->forks[i]), NULL);
        i++;
    }
       
}


void    *eat(void *philo)
{
    t_philo     *p;

    p = (t_philo*)philo; 
    pthread_mutex_lock(&(p->state->forks[p->left_fork]));
    print(philo, "has taken left_fork");
    pthread_mutex_lock(&(p->state->forks[p->right_fork]));
    print(philo, "has taken right_fork");
    p->die_t = get_time() - p->state->start_time + p->die_t;
    print(philo, "is eating");
    usleep(p->state->time_to_eat * 1000);
    print(philo, "has left right_fork");
    print(philo, "has left left_fork");
    pthread_mutex_unlock(&(p->state->forks[p->right_fork]));
    pthread_mutex_unlock(&(p->state->forks[p->left_fork]));
    if (p->state->must_eat != -1)
        p->eat_number++;
    return NULL;
}

void    _sleep(void *philo)
{
    t_philo *p;

    p = (t_philo*)philo;
    print(philo, "is sleeping");
    usleep(p->state->time_to_sleep * 1000);
}

void    *think(void *philo)
{
    t_philo *p;

    p = (t_philo*)p;
    print(p,"is thinking");
    return NULL;
}

void    *check_die(void *philo)
{
    t_philo *p;

    p = (t_philo*)philo;
    while(1)
    {   
        if ((get_time() - p->state->start_time ) > p->die_t)
        {
            pthread_mutex_lock(&p->state->print_mutex);
            printf("\033[0;31m%llu\t%d\tdied\033[0m\n", get_time() - p->state->start_time, p->id);
            pthread_mutex_unlock(&p->state->simulation);
        }
        if (p->state->counter == p->state->philosophers)
        {
            pthread_mutex_lock(&p->state->print_mutex);
            printf("\033[0;31m%llu\t%d\tSimulatuion end\033[0m\n", get_time() - p->state->start_time, p->id);
            pthread_mutex_unlock(&p->state->simulation);
        }
        usleep(500);
    }
    return NULL;
}

void    *routine(void  *philo)
{
    t_philo *p;
    pthread_t pthread_id;

    p = (t_philo*)philo;
    p->die_t  = get_time() - p->state->start_time + p->state->time_to_die;
    pthread_create(&pthread_id, NULL, check_die, philo);
    while (1)
    {
        eat(philo);
        _sleep(philo);
        think(philo);
        if (p->eat_number == p->state->must_eat)
            p->state->counter++;
        if (p->state->counter == p->state->philosophers)
            break; 
    }
    return NULL;
}

void    philo_create(t_philo *philo, t_state *state)
{
    int i;

    i = 0;
    while(i < state->philosophers)
    {
       if (pthread_create(&philo[i].pthread_id , NULL, routine, (void*)&philo[i]))
        {
            ft_putstr("pthread_create() error");
            exit (1);
        }
        i++;
        usleep(100);
    }
}

int main(int c, char **argv)
{
    t_philo *philo;
    t_state *state;

    state = (t_state*)malloc(sizeof(t_state));
    parsing(c, argv, state);
    philo = malloc(sizeof(t_philo) * state->philosophers);
    state_init(state);
    philo_init(philo, state);
    state->start_time = get_time();
    philo_create(philo, state);
    pthread_mutex_lock(&state->simulation);
    return (0);
}






































