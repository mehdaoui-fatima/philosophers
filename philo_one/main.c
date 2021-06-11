#include "philo_one.h"

uint64_t get_time()//millisec
{   
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void    print(t_philo *philo, char *task_type)
{
    pthread_mutex_lock(&philo->s->print_mutex);
    printf("%llu thread %d %s\n",(get_time() - philo->s->start_time), philo->id, task_type);
    pthread_mutex_unlock(&philo->s->print_mutex);
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
        philo[i].die_t = 0;
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % n;
        philo[i].eat_number = 0;
      
        // printf("philo %d|left_fork %d|right_fork %d \n",i , philo[i].left_fork, philo[i].right_fork);
        i++;
    }
}


void    *eat(void *philo)
{
    t_philo     *p;
    long long   current_time;

    p = (t_philo*)philo; 
    pthread_mutex_lock(&(p->s->forks[p->left_fork]));
    print(philo, "has taken left_fork");
    // printf("%llu thread %d has taken right_fork %d\n",(get_time() - p->s->start_time), p->id, p->right_fork);
    pthread_mutex_lock(&(p->s->forks[p->right_fork]));
    print(philo, "has taken right_fork");
    // printf("%llu thread %d has taken left_fork %d\n",(get_time() - p->s->start_time), p->id, p->left_fork);
    p->die_t = get_time() - p->s->start_time + p->die_t;
    print(philo, "is eating");
    usleep(p->s->time_to_eat * 1000);
    print(philo, "has left right_fork");
    print(philo, "has left left_fork");
    // printf("%llu thread %d has left right_fork %d and left_fork %d\n",(get_time() - p->s->start_time), p->id, p->right_fork, p->left_fork);
    pthread_mutex_unlock(&(p->s->forks[p->right_fork]));
    pthread_mutex_unlock(&(p->s->forks[p->left_fork]));
    if (p->s->number_of_times_each_philosopher_must_eat != -1)
        p->eat_number++;
    return NULL;
}

void    _sleep(void *philo)
{
    t_philo *p;

    p = (t_philo*)philo;
    print(philo, "is sleeping");
    usleep(p->s->time_to_sleep * 1000);
}

void    *think(void *philo)
{
    t_philo *p;

    p = (t_philo*)p;
    print(p, "is thinking");
    return NULL;
}

void    *check_die(void *philo)
{
    t_philo *p;

    p = (t_philo*)philo;
    while(1)
    {   
        if ((get_time() - p->s->start_time ) > p->die_t)
        {
            // printf("%llu|%llu thread %d died|\n",(get_time() - p->s->start_time), p->die_t, p->id);
            pthread_mutex_lock(&p->s->print_mutex);
            printf("\033[0;31m%llu\t%d\tdied\033[0m\n", get_time() - p->s->start_time, p->id);
            pthread_mutex_unlock(&p->s->simulation);
        }
        if (p->s->counter == p->s->number_of_philosophers)
        {
            // print(p, "has eat number_of_times_each_philosopher_must_eat ");
            pthread_mutex_lock(&p->s->print_mutex);
            printf("\033[0;31m%llu\t%d\tDone\033[0m\n", get_time() - p->s->start_time, p->id);
            pthread_mutex_unlock(&p->s->simulation);
            // break;
        }
        usleep(500);//1 millisec
        // printf("%llu|%llu|thread %d\n",(get_time() - p->s->start_time), p->die_t, p->id);
    }
    return NULL;
}

void    *routine(void  *philo)
{
    t_philo *p;
    pthread_t pthread_id;

    p = (t_philo*)philo;
    p->die_t  = get_time() - p->s->start_time + p->s->time_to_die;
    pthread_create(&pthread_id, NULL, check_die, philo);
    while (1)
    {
        eat(philo);
        _sleep(philo);
        think(philo);
        if (p->eat_number == p->s->number_of_times_each_philosopher_must_eat)
            p->s->counter++;
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
    pthread_mutex_init(&state->print_mutex, NULL);
    pthread_mutex_lock(&state->simulation);
    state->philo_died = 0;
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
        usleep(100);
    }
    // sleep(2);
    /* lock simulation() will let principal thread stack because the simulation mutex he tried to lock already locked,
     main will continue until simulation unlocked by another tried in case of death of one of philosophers*/
    pthread_mutex_lock(&state->simulation);
    // pthread_mutex_unlock(&state->simulation);
    // ft_putstr("from main...\n");
    return (0);
}






































