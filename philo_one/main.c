#include "philo_one.h"


void    *execute(void *st)
{
    long long  *s =(long long*)st;
    printf("im the %ld\n",s);
    return NULL;
}


int main(int c, char **argv)
{
    t_state *state;
    char *s="thread1";
    char *s2="thread2";

    state = malloc(sizeof(t_state));
    parsing(c, argv, state);
    printf("%d %d %d %d %d \n", state->number_of_philosophers, state->time_to_die, state->time_to_eat, state->time_to_sleep, state->number_of_times_each_philosopher_must_eat);
    printf("from main\n");
    // pthread_t t1, t2;
    // int err1, err2;
    // err1 = pthread_create(&t1, NULL, execute, (void*)s);
    // err2 = pthread_create(&t2, NULL, execute, (void*)s2);
    // pthread_detach(t1);
    // pthread_detach(t2);
    int i=0;
    pthread_t threads_id[state->number_of_philosophers];
    
    while(i < state->number_of_philosophers)
    {
       if (pthread_create(&threads_id[i], NULL, execute, (void*)&threads_id[i]) != 0)
        {
            ft_putstr("pthread_create() error");
            exit (1);
        }
        i++;
    }
    sleep(3);
    ft_putstr("from main...\n");


}






































