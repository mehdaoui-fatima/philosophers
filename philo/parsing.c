#include "philo.h"



void    parsing(int c, char **argv, t_state *state)
{
    int *args;
    int i;
    int j;
    int  optional;

    i = 0;
    j = 0;
    args = malloc(sizeof(int) * c - 1);
    if (c < 5)
    {
        ft_putstr(INSU_ARGS); 
        exit(1);
    }else if ( c > 6)
    {
        ft_putstr(MANY_ARGS);
         exit(1);
    }
    else
    {
        while(++i < c)
          args[j++] = ft_atoi(argv[i]);
        // print_args(args,j);
        if (!ft_ispositive(args, c - 1))
        {
            ft_putstr(RED_ POS_VALUES NRM_);
            exit(1);
        }
        if (args[0] < 1 || args[0] > 200)
        {
            ft_putstr(FALSE_VALUES);
            exit (1);
        }
        if (args[1] < 60 || args[2] < 60 || args[3] < 60)
        {
            ft_putstr(FALSE_TIME);
            exit (1);
        }
        state->philosophers = args[0];
        state->time_to_die = args[1];
        state->time_to_eat = args[2];
        state->time_to_sleep = args[3];
        state->must_eat = (c == 6)? args[4] : -1;
        state->counter = 0;
    }




}
