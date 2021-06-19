#include "philo.h"


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






































