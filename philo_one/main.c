#include "philo_one.h"


int	ft_atoi(char *s)
{
	int				i;
	unsigned long	res;
	int				n;

	i = 0;
	res = 0;
	n = 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
			|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		n = (s[i] == '-') ? -1 : 1;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - '0');
		if (res > LONG_MAX && n == 1)
			return (-1);
		if (res > LONG_MAX && n == -1)
			return (0);
		i++;
	}
	return ((int)(res * n));
}


int ft_ispositive(int *s, int n)
{
   
    int i;

    i = 0;
    while(i < n)
    {
        
        if (s[i] < 0)
           return(0);
        i++;
    }
    return (1);
}





int main(int c, char **argv)
{
    int *args;
    int i;
    int j;


    i = 0;
    j = 0;
    args = malloc(sizeof(int) * c - 1);
    if (c != 5 && c != 6)
    {
        printf("uncorrect number of arguments\n");
        exit(1);
    }  
    while(++i < c)
        args[j++] = ft_atoi(argv[i]);
    i = 0;
    while(i < j)
    {
        printf("%d\n",args[i]);
        i++;
    }
    if (!ft_ispositive(args, c - 1))
    {
        printf("arguments should be positive\n");
        exit(1);
    }
       
    
        
    

}

















































// void    *eat(void* sth)
// {   
//     char *value = (char*)sth;
//     printf("from thread \n thread_%s is eating...\n", value);
//     return NULL;
// }


// int main(int *c, char** argv)
// {

    // pthread_t pthread_id;
    // int err;
    // char *value = "nouhaila";
    // err = pthread_create(&pthread_id, NULL, eat, (void*)value);
    // if (err)
    // {
    //     printf("cant create thread..\n");
    //     return (1);
    // }
    // pthread_join(pthread_id, NULL);
    // printf("from main\n");


    // return (0);
// }